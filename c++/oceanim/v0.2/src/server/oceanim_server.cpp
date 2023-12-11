/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 07:15:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 11:54:28
 * @FilePath: /c++/oceanim/v0.2/src/server/oceanim_server.cpp
 * @Description: 注释信息
 */
#include "oceanim_server.h"
#include <nlohmann/json.hpp>
#include <functional>
#include <string>
#include "oceanim_service.h"

void OceanIMServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    // 客户断开连接
    if (!conn->connected())
    {
        conn->shutdown();
    }
}

void OceanIMServer::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp time)
{
    std::string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    nlohmann::json js = nlohmann::json::parse(buf);
    // 用于实现：完全解耦合 网络模块代码与业务模块代码
    // 通过js["msgid"] 获取---->业务handler---->回调conn js time
    auto msgHandler = OceanIMService::instance()->getHandler(js["msgcate"].get<int>());
    // 回调消息category绑定的事件处理器， 来执行业务处理
    msgHandler(conn, js, time);
}

OceanIMServer::OceanIMServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr, const std::string &nameArg) : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册连接断开回调
    _server.setConnectionCallback(std::bind(&OceanIMServer::onConnection, this, std::placeholders::_1));

    // 注册读写回调
    _server.setMessageCallback(std::bind(&OceanIMServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置线程
    _server.setThreadNum(4);
}

void OceanIMServer::start()
{
    _server.start();
}

OceanIMServer::~OceanIMServer()
{
}