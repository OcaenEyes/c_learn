/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-11 08:30:33
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-11 09:30:03
 * @FilePath: /c++/knowledge/c++重写muduo库/include/tcpconnection.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"
#include "inetaddress.h"
#include "callbacks.h"
#include "buffer.h"
#include "timestamp.h"

#include <memory>
#include <string>
#include <atomic>

namespace ocean_muduo
{

    class channel;
    class eventloop;
    class socket;

    // 表示已连接客户端通信的一条连接
    //  tcpserver ---> 通过 acceptor ---> 当有个新用户连接， 通过accept函数达到connfd
    //  ===> tcpconnection 设置回调 ==> channel ====> 再触发poller===> channel的回调操作
    class tcpconnection : public noncopyable, public std::enable_shared_from_this<tcpconnection>
    {

    public:
        tcpconnection(eventloop *loop,
                      const std::string name,
                      int sockfd,
                      const inetaddress &local_addr,
                      const inetaddress &peer_addr);
        ~tcpconnection();

        eventloop *get_loop() const;
        const std::string &get_name() const;
        const inetaddress &get_local_addr() const;
        const inetaddress &get_peer_addr() const;

        bool get_connected() const;

        // 发送数据
        void send(const void *message, int len);

        // 关闭连接
        void shutdown();

        // 连接建立
        void connect_established();

        // 连接销毁
        void connect_destroyed();

        void set_connection_callback(const ConnectionCallback &cb);
        void set_message_callback(const MessageCallback &cb);
        void set_write_callback(const WriteCallback &cb);
        void set_high_water_mark_callback(const HighWaterMarkCallback &cb);
        void set_close_callback(const CloseCallback &cb);

    private:
        enum StateE
        { // 连接状态
            k_disconnected,
            k_connecting,
            k_connected,
            k_disconnecting
        };
        eventloop *loop_; // 此处一定不是 baseloop_, 由于tcpconnection 一直是在subloop中管理的
        const std::string name_;

        std::atomic_int state_;
        bool reading_;

        std::unique_ptr<socket> socket_;
        std::unique_ptr<channel> channel_;

        const inetaddress local_addr_;
        const inetaddress peer_addr_;

        ConnectionCallback connection_callback_; // 有新连接时的callback
        MessageCallback message_callback_;       // 有读写消息的时callback
        WriteCallback write_callback_;           // 消息发送完成以后的callback

        HighWaterMarkCallback high_water_mark_callback_;
        CloseCallback close_callback_;

        size_t high_water_mark_;

        buffer input_buffer_;
        buffer output_buffer_;

        void handle_read(timestamp receive_time);
        void handle_write();
        void handle_close();
        void handle_error();

        void send_in_loop(const void *message, size_t len);
        void shutdown_in_loop();
    };

} // namespace ocean_muduo
