/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 09:37:22
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 10:01:04
 * @FilePath: /c++/oceanim/v0.2/include/oceanim_service.h
 * @Description: service服务【业务类】
 */
#pragma once
#include <unordered_map>
#include <functional>
#include "muduo/net/TcpConnection.h"
#include <nlohmann/json.hpp>

using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)>;

class OceanIMService
{
private:
    OceanIMService(/* args */);

    std::unordered_map<int, MsgHandler> _msgHandlerMap; // 消息处理器的map【id:业务处理方法】

public:
      // 获取单例对象的接口函数
    static OceanIMService *instance();
    // 登录业务
    void login(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);
    // 注册业务
    void regist(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgcate);
};
