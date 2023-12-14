/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 09:37:22
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 02:38:56
 * @FilePath: /c++/oceanim/v0.2/include/oceanim_service.h
 * @Description: service服务【业务类】
 */
#pragma once
#include <unordered_map>
#include <functional>
#include <mutex>
#include "muduo/net/TcpConnection.h"
#include <nlohmann/json.hpp>
#include "model/user_model.h"
#include "model/onechat_model.h"

using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)>;

class OceanIMService
{
private:
    OceanIMService(/* args */);
    // 消息处理器的map【id:业务处理方法】
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接
    std::unordered_map<int, muduo::net::TcpConnectionPtr> _userConnMap;

    // 定义互斥锁， 保证_userConnMap的线程安全
    std::mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    OneChatModel _oneChatModel;

public:
    // 获取单例对象的接口函数
    static OceanIMService *instance();
    // 登录业务
    void login(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);
    // 注册业务
    void regist(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);

    // 请求参数异常
    void errreq(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);

    // 一对一聊天
    void oneChat(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);

    // 发送好友请求\处理好友请求、添加成功
    void addFriend(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);


    // 群聊天
    void groupChat(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgcate);

    // 处理服务器异常后，业务重置方法
    void reset();

    // 处理客户端异常退出
    void clientCloseException(const muduo::net::TcpConnectionPtr &conn);
};
