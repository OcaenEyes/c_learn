/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 09:53:29
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 11:28:18
 * @FilePath: /c++/oceanim/v0.2/src/server/oceanim_service.cpp
 * @Description: service服务类的实现
 */
#include "oceanim_service.h"
#include "common/common.h"
#include "muduo/base/Logging.h"
#include <string>

OceanIMService::OceanIMService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&OceanIMService::login, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({REGIST_MSG, std::bind(&OceanIMService::regist, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
}

// 获取单例对象的接口函数
OceanIMService *OceanIMService::instance()
{
    static OceanIMService service; // 静态局部变量， 初始化以后就不会变化了
    return &service;
}

// 登录
void OceanIMService::login(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do login service!\n");
}

// 注册
void OceanIMService::regist(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do regist service!\n");
}

MsgHandler OceanIMService::getHandler(int msgcate)
{
    // 记录错误日志，msgcate没有对应的事件处理
    auto it = _msgHandlerMap.find(msgcate);
    if (it == _msgHandlerMap.end()) // 没有找到
    {
        // 返回一个默认的空处理器
        return [=](const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
        {
            LOG_ERROR << "msgcate:" << msgcate << "can not find handler!\n";
        };
    }
    else
    {
        return _msgHandlerMap.at(msgcate);
    }
}
