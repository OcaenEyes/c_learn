/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 21:56:26
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-12 08:07:05
 * @FilePath: /c++/knowledge/c++重写muduo库/src/tcpserver.cpp
 * @Description: 注释信息
 */
#include "tcpserver.h"
#include "logger.h"

#include <strings.h>

namespace ocean_muduo
{
    eventloop *check_loop_not_null(eventloop *loop)
    {
        if (loop == nullptr)
        {
            LOG_FATAL("%s:%s:%d mainloop is null!\n", __FILE__, __FUNCTION__, __LINE__);
        }
        return loop;
    }

    // 构造
    tcpserver::tcpserver(eventloop *loop, const inetaddress &listen_addr, const std::string &name, Option opt)
        : loop_(check_loop_not_null(loop)),
          ip_port_(listen_addr.to_ip_port()),
          name_(name),
          acceptor_(new acceptor(loop, listen_addr, opt)),
          thread_pool_(new eventloop_thread_pool(loop, name_)),
          connection_callback_(),
          message_callback_(),
          next_conn_id_(1),
          started_(0)
    {
        // 当有新用户连接时候， 会执行 tcpserver::new_connection回调
        acceptor_->set_new_connection_callback(std::bind(&tcpserver::new_connection, this, std::placeholders::_1, std::placeholders::_2));
    }

    tcpserver::~tcpserver()
    {
        LOG_INFO("tcpserver::~tcpserver() [%s] destructing\n", name_.c_str());
        for (auto &i : connections_)
        {
            // 这个局部的shared_ptr智能指针对象，出右括号后可以自动释放new出来的tcpconnection对象
            TcpConnectionPtr conn(i.second);
            i.second.reset();

            // 销毁连接
            conn->get_loop()->run_in_loop(
                std::bind(&tcpconnection::connect_destroyed, conn));
        }
    }

    void tcpserver::set_thread_init_callback(const std::function<void(eventloop *)> &cb)
    {
        thread_init_callback_ = cb;
    }

    void tcpserver::set_connection_callback(const ConnectionCallback &cb)
    {
        connection_callback_ = cb;
    }

    void tcpserver::set_message_callback(const MessageCallback &cb)
    {
        message_callback_ = cb;
    }

    void tcpserver::set_write_complete_callback_(const WriteCompleteCallback &cb)
    {
        write_complete_callback_ = cb;
    }

    void tcpserver::set_thread_num(int num)
    {
        thread_pool_->set_thread_num(num);
    }

    // 开启服务器监听
    void tcpserver::start()
    {
        if (started_++ == 0) // 防止一个tcpserver 对象start多次
        {
            thread_pool_->start(thread_init_callback_); // 启动底层的线程池
            loop_->run_in_loop(std::bind(&acceptor::listen, acceptor_.get()));
        }
    }

    // 当有一个新的客户端连接， acceptor_会执行这个回调函数操作
    void tcpserver::new_connection(int sockfd, const inetaddress &peer_addr)
    {
        // 轮询算法， 选择一个subloop, 来管理channel
        eventloop *io_loop = thread_pool_->get_next_loop();
        char buf[64] = {0};
        snprintf(buf, sizeof(buf), "-%s#%d", ip_port_.c_str(), next_conn_id_);
        ++next_conn_id_;
        std::string conn_name = name_ + buf;
        LOG_INFO("tcpserver::new_connection [%s] - new connection [%s] from %s\n",
                 name_.c_str(), conn_name.c_str(), ip_port_.c_str());

        // 通过sockfd获取其绑定的本机 ip地址和端口信息
        sockaddr_in local;
        bzero(&local, sizeof(local));
        socklen_t addr_len = sizeof(local);
        if (::getsockname(sockfd, (sockaddr *)&local, &addr_len) < 0)
        {
            LOG_ERROR("sockets::get_local_addr");
        }

        inetaddress local_addr(local);

        //  根据连接成功的sockfd， 创建tcpconnection对象
        TcpConnectionPtr conn(new tcpconnection(
            io_loop,
            conn_name,
            sockfd,
            local_addr,
            peer_addr));

        connections_[conn_name] = conn;
        // 下面的回调都是用户设置给 tcpserver ，再触发tcpconnection , 再触发channel，再到poller， notify channel调用回调
        conn->set_connection_callback(connection_callback_);
        conn->set_message_callback(message_callback_);
        conn->set_write_complete_callback_(write_complete_callback_);

        // 设置了如何关闭连接到回调
        conn->set_close_callback(std::bind(&tcpserver::remove_connection, this, std::placeholders::_1));

        // 直接调用 tcpconnection::connect_established()
        io_loop->run_in_loop(std::bind(&tcpconnection::connect_established, conn));
    }

    void tcpserver::remove_connection(const TcpConnectionPtr &conn)
    {
        loop_->run_in_loop(std::bind(&tcpserver::remove_connection_in_loop, this, conn));
    }

    void tcpserver::remove_connection_in_loop(const TcpConnectionPtr &conn)
    {
        LOG_INFO("tcpserver::remove_connection_in_loop [%s] -connection %s\n", name_.c_str(), conn->get_name().c_str());

        connections_.erase(conn->get_name());
        eventloop *ioloop = conn->get_loop();

        ioloop->queue_in_loop(
            std::bind(&tcpconnection::connect_destroyed, conn));
    }

} // namespace ocean_muduo