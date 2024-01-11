/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 07:38:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-11 21:36:58
 * @FilePath: /c++/knowledge/c++重写muduo库/src/tcpconnection.cpp
 * @Description: 注释信息
 */
#include "tcpconnection.h"
#include "logger.h"
#include "socket.h"
#include "channel.h"
#include "eventloop.h"

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

    tcpconnection::tcpconnection(eventloop *loop, const std::string name, int sockfd, const inetaddress &local_addr, const inetaddress &peer_addr)
        : loop_(check_loop_not_null(loop)),
          name_(name),
          state_(k_connecting),
          reading_(true),
          socket_(new socket(sockfd)),
          channel_(new channel(loop, sockfd)),
          local_addr_(local_addr),
          peer_addr_(peer_addr),
          high_water_mark_(64 * 1024 * 1024) // 64M
    {
        // 下面给channel_设置相应的回调函数，poller给channel通知感兴趣的事件发生了， channel会回调相应的操作函数
        channel_->set_read_callback(std::bind(&tcpconnection::handle_read, this, std::placeholders::_1));
        channel_->set_write_callback(std::bind(&tcpconnection::handle_write, this));
        channel_->set_error_callback(std::bind(&tcpconnection::handle_error, this));

        LOG_INFO("tcpconnection::ctor[%s] as fd=%d \n", name_.c_str(), sockfd);
        socket_->set_keep_alive(true); // 保活机制
    }

    tcpconnection::~tcpconnection()
    {
        LOG_INFO("tcpconnection::dtor[%s] as fd=%d state=%d\n", name_.c_str(), channel_->fd(), state_);
    }

    eventloop *tcpconnection::get_loop() const
    {
        return nullptr;
    }

    const std::string &tcpconnection::get_name() const
    {
        return name_;
    }

    const inetaddress &tcpconnection::get_local_addr() const
    {
        return local_addr_;
    }

    const inetaddress &tcpconnection::get_peer_addr() const
    {
        return peer_addr_;
    }

    bool tcpconnection::get_connected() const
    {
        return state_ == k_connected;
    }

    void tcpconnection::send(const void *message, int len)
    {
    }

    void tcpconnection::shutdown()
    {
    }

    void tcpconnection::connect_established()
    {
    }

    void tcpconnection::connect_destroyed()
    {
    }

    void tcpconnection::set_connection_callback(const ConnectionCallback &cb)
    {
        connection_callback_ = cb;
    }

    void tcpconnection::set_message_callback(const MessageCallback &cb)
    {
        message_callback_ = cb;
    }

    void tcpconnection::set_write_callback(const WriteCallback &cb)
    {
        write_callback_ = cb;
    }

    void tcpconnection::set_high_water_mark_callback(const HighWaterMarkCallback &cb)
    {
        high_water_mark_callback_ = cb;
    }

    void tcpconnection::set_close_callback(const CloseCallback &cb)
    {
        close_callback_ = cb;
    }

    void tcpconnection::handle_read(timestamp receive_time)
    {
        int saved_errno = 0;
        ssize_t n = input_buffer_.read_fd(channel_->fd(), &saved_errno);
        if (n > 0)
        {
            // 已建立连接的用户，有可读事件发生了，调用用户传入的回调操作onMessage
            message_callback_(std::shared_from_this(), &input_buffer_, receive_time);
        }
        else if (n == 0)
        {
            handle_close();
        }
        else
        {
            errno = saved_errno;
            LOG_ERROR("tcpconnection::handle_read errnor ,errno:%d",errno);
            handle_error();
        }
    }

    void tcpconnection::handle_write()
    {
        if (channel_->is_writing())
        {
            /* code */
        }
        
    }

    void tcpconnection::handle_close()
    {
    }

    void tcpconnection::handle_error()
    {
    }

    void tcpconnection::send_in_loop(const void *message, size_t len)
    {
    }

    void tcpconnection::shutdown_in_loop()
    {
    }
} // namespace ocean_muduo
