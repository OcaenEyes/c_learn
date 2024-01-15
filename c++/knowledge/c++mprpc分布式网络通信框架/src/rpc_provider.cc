/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:57:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 03:13:50
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/rpc_provider.cc
 * @Description: 注释信息
 */
#include "rpc_provider.h"
#include "ocean_mprpc_application.h"

#include <functional>

RpcProvider::RpcProvider(/* args */)
{
}

RpcProvider::~RpcProvider()
{
}

void RpcProvider::NotifyService(google::protobuf::Service *servcie)
{
}

void RpcProvider::Run()
{
    std::string ip = OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    muduo::net::InetAddress addres(ip, port);

    // 创建 TcpServer对象
    muduo::net::TcpServer tcpserver(&m_eventloop, addres, "RpcProvider");

    // 绑定连接回调 和消息读写回调方法【分离网络代码 和 业务代码】
    tcpserver.setConnectionCallback(std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    tcpserver.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库的线程数量
    tcpserver.setThreadNum(3);
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp receive_time)
{
}
