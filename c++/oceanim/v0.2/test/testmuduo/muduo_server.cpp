/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-10 14:22:01
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-10 15:16:43
 * @FilePath: /c++/oceanim/v0.2/src/muduo_server.cpp
 * @Description: muduo网络库 给用户提供了两个主要的类
 *              TcpServer:用于编写服务器程序
 *              TcpClient:用于编写客户端程序
 *       epoll+ 线程池
 *       好处： 能把网络的I/O的代码 和业务代码区分开
 *                      用户的连接和断开， 用户的可读写事件
 */
#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include <functional>
#include <iostream>
#include <string>

/**
 * 基于muduo网络库开发服务器程序
 *  1. 组合TcpServer对象
 *  2. 创建Event Loop事件循环对象的指针
 *  3. 明确TcpSever构造函数需要什么参数， 输出ChatServer的构造函数
 *  4. 在当前服务器类的构造函数中，注册处理连接的回调函数，注册处理消息读写的回调函数
 *  5. 设置服务器的线程数量， muduo库回自动分配I/O线程 和worker线程
 */
class ChatServer
{
private:
    muduo::net::TcpServer _server;
    muduo::net::EventLoop *_loop;

    // 专门处理用户的连接创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            std::cout << conn->peerAddress().toIpPort()
                      << "->"
                      << conn->localAddress().toIpPort()
                      << "->"
                      << "state:online"
                      << "\n";
        }
        else
        {
            std::cout << conn->peerAddress().toIpPort()
                      << "->"
                      << conn->localAddress().toIpPort()
                      << "->"
                      << "state:offline"
                      << "\n";
        }
    }

    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buffer, // 缓冲区
                   muduo::Timestamp time       // 接收到数据时的时间信息
    )
    {
        std::string buf = buffer->retrieveAllAsString();
        std::cout << "recv data:"
                  << buf
                  << "time:"
                  << time.toString()
                  << "\n";
        conn->send(buf);
    }

public:
    ChatServer(muduo::net::EventLoop *loop,               // 事件循环
               const muduo::net::InetAddress &listenAddr, // IP +Port
               const std::string &nameArg                 // 服务器的名字
               ) : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 设置服务器的线程数量，1个I/O线程， 3个worker线程
        _server.setThreadNum(4);
    }

    /// @brief 开启事件循环
    void start()
    {
        _server.start();
    }
};

int main()
{
    muduo::net::EventLoop loop; // epoll
    muduo::net::InetAddress addr("127.0.0.1", 12345);
    ChatServer server(&loop, addr, "OceanImServer");

    server.start();
    loop.loop(); // epoll_wait 以阻塞方式等待新用户连接， 已连接用户的读写事件

    return 0;
}