/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-09 08:24:20
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 09:17:58
 * @FilePath: /c++/knowledge/c++重写muduo库/include/tcpserver.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"
#include "eventloop.h"
#include "acceptor.h"
#include "inetaddress.h"
#include "eventloop_thread_pool.h"
#include "buffer.h"
#include "callbacks.h"
#include "tcpconnection.h"

#include <functional>
#include <atomic>
#include <unordered_map>
#include <string>

namespace ocean_muduo
{

    enum Option
    {
        k_no_reuse_port,
        k_reuse_port
    };

    /**
     * @brief 对外的服务器编程，使用的类
     *
     */
    class tcpserver : public noncopyable
    {

    public:
        // using ThreadInitCallback = std::function<void(eventloop *)>;
        tcpserver(eventloop *loop, const inetaddress &listen_addr, const std::string &name, Option opt = k_no_reuse_port);
        ~tcpserver();

        void set_thread_init_callback(const std::function<void(eventloop *)> &cb);

        void set_connection_callback(const ConnectionCallback &cb);

        void set_message_callback(const MessageCallback &cb);

        void set_write_callback(const WriteCallback &cb);

        // 设置底层 subloop的个数
        void set_thread_num(int num);

        // 开启服务器监听
        void start();

    private:
        using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

        eventloop *loop_; // baseloop 用户定义的loop
        const std::string ip_port_;
        const std::string name_;
        std::unique_ptr<acceptor> acceptor_;                 // 运行在mianloop， 主要任务是监听新连接事件
        std::shared_ptr<eventloop_thread_pool> thread_pool_; // one loop per thread

        ConnectionCallback connection_callback_; // 有新连接时的callback
        MessageCallback message_callback_;       // 有读写消息的时callback
        WriteCallback write_callback_;           // 消息发送完成以后的callback

        std::function<void(eventloop *)> thread_init_callback_; // loop线程初始化的回调

        std::atomic_int started_;

        int next_conn_id_;

        ConnectionMap connections_; // 保存所有的连接

        void new_connection(int sockfd, const inetaddress &peer_addr);
        void remove_connection(const TcpConnectionPtr &conn);
    };
} // namespace ocean_muduo
