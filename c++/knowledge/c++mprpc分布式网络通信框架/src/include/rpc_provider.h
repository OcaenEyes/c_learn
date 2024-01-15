/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:48:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 03:13:20
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/rpc_provider.h
 * @Description: 注释信息
 */
#pragma once

#include <memory>
#include <google/protobuf/service.h>

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "muduo/net/TcpConnection.h"
#include "muduo/net/Buffer.h"
#include "muduo/base/Timestamp.h"

/// @brief 框架提供的专门服务 发布rpc服务的网络对象类， 负责rpc服务发布
class RpcProvider
{
public:
    RpcProvider(/* args */);
    ~RpcProvider();
    // 这里是框架提供给外部使用，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *servcie);
    // 启动rpc服务节点，开始提供rpc远程调用服务
    void Run();

private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventloop;

    // 新的socket连接回调
    void onConnection(const muduo::net::TcpConnectionPtr &);
    // 已建立连接用户的读写事件回调
    void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);
};
