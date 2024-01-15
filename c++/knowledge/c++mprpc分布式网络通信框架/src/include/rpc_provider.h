/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:48:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 22:19:48
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/rpc_provider.h
 * @Description: 注释信息
 */
#pragma once

#include <unordered_map>
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
    /**
     * 需要生成一张表，记录服务对象，及其发布的所有的服务方法
     */
    void NotifyService(google::protobuf::Service *servcie);
    // 启动rpc服务节点，开始提供rpc远程调用服务
    void Run();

private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventloop;

    // service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service;                                                     // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_method_map; // 保存服务方法
    };

    std::unordered_map<std::string, ServiceInfo> m_service_map; // 保存注册成功的服务对象，及其服务方法的所有信息

    // 新的socket连接回调
    void onConnection(const muduo::net::TcpConnectionPtr &);
    // 已建立连接用户的读写事件回调
    void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr &, google::protobuf::Message *);
};
