/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 21:56:26
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 14:45:44
 * @FilePath: /c++/knowledge/c++重写muduo库/src/tcpserver.cpp
 * @Description: 注释信息
 */
#include "tcpserver.h"
#include "logger.h"

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
    }

    void tcpserver::set_thread_init_callback(const std::function<void(eventloop *)> &cb)
    {
    }

    void tcpserver::set_connection_callback(const ConnectionCallback &cb)
    {
    }

    void tcpserver::set_message_callback(const MessageCallback &cb)
    {
    }

    void tcpserver::set_write_callback(const WriteCallback &cb)
    {
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

    void tcpserver::new_connection(int sockfd, const inetaddress &peer_addr)
    {
    }

    void tcpserver::remove_connection(const TcpConnectionPtr &conn)
    {
    }

} // namespace ocean_muduo