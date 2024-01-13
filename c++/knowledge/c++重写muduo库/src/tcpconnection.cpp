/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 07:38:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-13 16:14:24
 * @FilePath: /c++/knowledge/c++重写muduo库/src/tcpconnection.cpp
 * @Description: 注释信息
 */
#include "tcpconnection.h"
#include "logger.h"
#include "socket.h"
#include "channel.h"
#include "eventloop.h"

#include <functional>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace ocean_muduo
{
    static eventloop *check_loop_not_null(eventloop *loop)
    {
        if (loop == nullptr)
        {
            LOG_FATAL("%s:%s:%d mainloop is null!\n", __FILE__, __FUNCTION__, __LINE__);
        }
        return loop;
    }

    // 构造
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
        channel_->set_write_complete_callback_(std::bind(&tcpconnection::handle_write, this));
        channel_->set_close_callback(std::bind(&tcpconnection::handle_close, this));
        channel_->set_error_callback(std::bind(&tcpconnection::handle_error, this));

        LOG_INFO("tcpconnection::ctor[%s] as fd=%d \n", name_.c_str(), sockfd);
        socket_->set_keep_alive(true); // 保活机制
    }

    // 析构
    tcpconnection::~tcpconnection()
    {
        LOG_INFO("tcpconnection::dtor[%s] as fd=%d state=%d\n", name_.c_str(), channel_->fd(), (int)state_);
    }

    eventloop *tcpconnection::get_loop() const
    {
        return loop_;
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

    // 发送数据
    void tcpconnection::send(const std::string &buf)
    {
        if (state_ == k_connected)
        {
            if (loop_->is_in_loopthread())
            {
                printf("send(const std::string &buf), buf is: %s", buf.c_str());
                send_in_loop(buf.c_str(), buf.size());
            }
            else
            {
                loop_->run_in_loop(std::bind(&tcpconnection::send_in_loop, this, buf.c_str(), buf.size()));
            }
        }
    }

    /// @brief 连接关闭
    void tcpconnection::shutdown()
    {
        if (state_ == k_connected)
        {
            set_state(k_disconnecting);
            loop_->run_in_loop(std::bind(&tcpconnection::shutdown_in_loop, this));
        }
    }

    /// @brief 连接建立
    void tcpconnection::connect_established()
    {
        set_state(k_connected);
        channel_->tie(shared_from_this());

        channel_->enable_reading(); // 向poller注册读事件 ，EPOLLIN

        // 新连接建立，执行回调
        connection_callback_(shared_from_this());
    }

    /// @brief 连接销毁
    void tcpconnection::connect_destroyed()
    {
        if (state_ == k_connected)
        {
            set_state(k_disconnected);
            channel_->disable_all(); // 把channel_感兴趣的所有事件，从poller中移除

            connection_callback_(shared_from_this());
        }
        channel_->remove();
    }

    // 设置connection_callback_
    void tcpconnection::set_connection_callback(const ConnectionCallback &cb)
    {
        connection_callback_ = cb;
    }

    // 设置message_callback_
    void tcpconnection::set_message_callback(const MessageCallback &cb)
    {
        message_callback_ = cb;
    }
    // 设置write_complete_callback_
    void tcpconnection::set_write_complete_callback_(const WriteCompleteCallback &cb)
    {
        write_complete_callback_ = cb;
    }
    // 设置high_water_mark_callback_
    void tcpconnection::set_high_water_mark_callback(const HighWaterMarkCallback &cb, size_t water_mark)
    {
        high_water_mark_callback_ = cb;
        high_water_mark_ = water_mark;
    }
    // 设置close_callback_
    void tcpconnection::set_close_callback(const CloseCallback &cb)
    {
        close_callback_ = cb;
    }

    // 读事件
    void tcpconnection::handle_read(timestamp receive_time)
    {
        int saved_errno = 0;
        ssize_t n = input_buffer_.read_fd(channel_->fd(), &saved_errno);
        if (n > 0)
        {
            // 已建立连接的用户，有可读事件发生了，调用用户传入的回调操作onMessage
            message_callback_(shared_from_this(), &input_buffer_, receive_time);
        }
        else if (n == 0)
        {
            handle_close();
        }
        else
        {
            errno = saved_errno;
            LOG_ERROR("tcpconnection::handle_read errnor ,errno:%d", errno);
            handle_error();
        }
    }

    // 写事件
    void tcpconnection::handle_write()
    {
        if (channel_->is_writing())
        {
            int saved_errno = 0;
            ssize_t n = output_buffer_.write_fd(channel_->fd(), &saved_errno);
            if (n > 0)
            {
                output_buffer_.retrieve(n);
                if (output_buffer_.readable_bytes() == 0)
                {
                    channel_->disable_writing();
                    if (write_complete_callback_)
                    {
                        loop_->queue_in_loop(
                            std::bind(write_complete_callback_, shared_from_this()));
                    }
                    if (state_ == k_disconnecting)
                    {
                        shutdown_in_loop();
                    }
                }
            }
            else
            {
                std::cout << "output_buffer_.write_fd ,n= " << n << "\n";
                LOG_ERROR("tcpconnection::handle_write error\n");
            }
        }
        else
        {
            LOG_ERROR("tcpconnection::handle_write error, fd=%d is down, no more writing!\n", channel_->fd());
        }
    }

    // 关闭事件
    void tcpconnection::handle_close()
    {
        LOG_INFO("tcpconnection::handle_close, fd=%d state=%d \n", channel_->fd(), (int)state_);
        set_state(k_disconnected);
        channel_->disable_all();

        TcpConnectionPtr conn_ptr(shared_from_this());
        // 执行连接关闭的回调
        connection_callback_(conn_ptr);
        // 关闭连接的回调
        close_callback_(conn_ptr); // 执行的是 tcpserver的remove_connection()操作
    }

    // 错误事件
    void tcpconnection::handle_error()
    {
        int optval;
        socklen_t optlen = sizeof(optval);
        int err = 0;
        if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
        {
            err = errno;
        }
        else
        {
            err = optval;
        }

        LOG_ERROR("tcpconnection::handle_error, name:%s - SO_ERROR:%d\n ", name_.c_str(), err);
    }

    // 发送数据， 应用写的快，而内核发送数据慢， 需要把待发送数据写入缓冲区，并且设置水位回调
    void tcpconnection::send_in_loop(const void *message, size_t len)
    {
        ssize_t n_write = 0;
        ssize_t remaining = len;
        bool fault_err = false;

        printf("send_in_loop(const void *message, size_t len), message is: %s", message);
        // 之前调用过该connection的shutdown， 不能再进行发送了
        if (state_ == k_disconnected)
        {
            LOG_ERROR("disconnected, give up writing!");
            return;
        }

        if (!channel_->is_writing() && output_buffer_.readable_bytes() == 0)
        {
            n_write = ::write(channel_->fd(), message, len);
            if (n_write >= 0)
            {
                remaining = len - n_write;
                if (remaining == 0 && write_complete_callback_)
                {
                    // 既然这里 数据全部发送完成， 则就可以不用给channel 设置epollout事件了
                    loop_->queue_in_loop(
                        std::bind(write_complete_callback_, shared_from_this()));
                }
            }
            else // n_write<0
            {
                n_write = 0;
                if (errno != EWOULDBLOCK)
                {
                    LOG_ERROR("tcpconnection::send_in_loop");
                    if (errno == EPIPE || errno == ECONNRESET) // SIGPIPE 、 RESET
                    {
                        fault_err = true;
                    }
                }
            }
        }
        //  说明当前这一次没有把数据全部发送出去， 剩余的数据需要保存到缓冲区当中，然后给channel 注册epollout事件， poller发现tcp的发送缓冲区有空间
        //      会通知相应的sock - channel，注册epollout事件， poller发现tcp的发送缓冲区有空间，会通知相应的sock-channel, 调用 write_callback_方法
        //      也就是，调用tcpconnection::handle_write()方法， 把发送缓冲区中的数据全部发送完成
        if (!fault_err && remaining > 0)
        {
            ssize_t old_len = output_buffer_.readable_bytes();
            if (old_len + remaining >= high_water_mark_ && old_len < high_water_mark_ && high_water_mark_callback_)
            {
                // 触发 水位线回调
                loop_->queue_in_loop(std::bind(high_water_mark_callback_, shared_from_this(), old_len + remaining));
            }
            output_buffer_.append((char *)message + n_write, remaining);

            if (!channel_->is_writing())
            {
                channel_->enable_writing(); // 注册channel_的写事件，否则poller不会给channel 通知epollout
            }
        }
    }

    void tcpconnection::shutdown_in_loop()
    {
        if (!channel_->is_writing())
        {                              // 说明 output_buffer_中的数据已全部发送完成
            socket_->shutdown_write(); // 关闭写端
        }
    }

    void tcpconnection::set_state(StateE state)
    {
        state_ = state;
    }
} // namespace ocean_muduo
