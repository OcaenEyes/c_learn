/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 05:52:22
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-18 06:28:24
 * @FilePath: /c++/oceanim/v0.2/include/oceanim_server.h
 * @Description: server服务器
 */
#pragma once

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/base/Logging.h"

class OceanIMServer
{
private:
    muduo::net::TcpServer _server;
    muduo::net::EventLoop *_loop;

    void onConnection(const muduo::net::TcpConnectionPtr &conn);
    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buffer, // 缓冲区
                   muduo::Timestamp time       // 接收到数据时的时间信息
    );

public:
    OceanIMServer(muduo::net::EventLoop *loop,               // 事件循环
                  const muduo::net::InetAddress &listenAddr, // IP +Port
                  const std::string &nameArg                 // 服务器的名字
    );                                                       // 初始化聊天服务器对象
    void start();                                           // 启动服务
    ~OceanIMServer();
};
