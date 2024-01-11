/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 07:38:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-11 09:39:07
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
    }

    tcpconnection::~tcpconnection()
    {
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
    }

    void tcpconnection::handle_write()
    {
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
