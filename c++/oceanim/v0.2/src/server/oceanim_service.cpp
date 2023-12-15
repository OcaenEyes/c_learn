/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 09:53:29
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-15 08:54:31
 * @FilePath: /c++/oceanim/v0.2/src/server/oceanim_service.cpp
 * @Description: service服务类的实现
 */
#include "oceanim_service.h"
#include "common/common.h"
#include "muduo/base/Logging.h"
#include <string>

OceanIMService::OceanIMService()
{
    _msgHandlerMap.insert({ERR_REQ, std::bind(&OceanIMService::errreq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&OceanIMService::login, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({REGIST_MSG, std::bind(&OceanIMService::regist, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({ONE_CHAT_MSG, std::bind(&OceanIMService::oneChat, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({GROUP_CHAT_MSG, std::bind(&OceanIMService::groupChat, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({FRIEND_REQ_RES, std::bind(&OceanIMService::addFriend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({CREATE_GROUP_MSG, std::bind(&OceanIMService::createGroup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    _msgHandlerMap.insert({ADD_GROUP_MSG, std::bind(&OceanIMService::addGroup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
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
    nlohmann::json response;
    try
    {
        int id = js["id"].get<int>();
        std::string password = js["password"];

        User user = _userModel.queryById(id);

        if (user.getId() == id && user.getPassword() == password)
        {
            if (user.getState() == "online")
            {
                // 不允许重复登录
                response["msgcate"] = LOGIN_MSG_ACK;
                response["id"] = user.getId();
                response["errno"] = 2;
                response["errmsg"] = "该账号已登录,请登录其他账号使用";
            }
            else
            {
                // 登录成功， 需要更新用户状态信息 state:offline->online
                user.setState("online");
                _userModel.update(user);

                response["msgcate"] = LOGIN_MSG_ACK;
                response["id"] = user.getId();
                response["name"] = user.getName();
                response["errno"] = 0;

                { // 加{}就表示作用域, 加锁解锁操作
                    std::lock_guard<std::mutex> lock(_connMutex);
                    _userConnMap.insert({id, conn});
                }

                // 登录成功之后则查询好友列表
                std::vector<User> friends_vec = _friendModel.query(id);
                if (!friends_vec.empty())
                {
                    Friends temp = Friends(friends_vec);
                    Friends::to_json(response, temp);
                }

                // 登录成功之后查询群列表
                std::vector<Group> groups_vec = _groupModel.qeuryGroups(id);
                if (!groups_vec.empty())
                {
                }

                // 登录成功之后则查询是否有未接收的离线消息
                std::vector<OneChat> onechats_vec = _oneChatModel.queryByUserId(id);

                if (!onechats_vec.empty())
                {
                    OneChats temp = OneChats(onechats_vec);
                    OneChats::to_json(response, temp);
                    for (int i = 0; i < onechats_vec.size(); i++)
                    {
                        // 消息读取之后修改消息状态
                        _oneChatModel.update(onechats_vec.at(i).getId());
                    }
                }
            }
        }
        else
        {
            // 账号密码错误
            response["msgcate"] = LOGIN_MSG_ACK;
            response["id"] = user.getId();
            response["errno"] = 1;
            response["errmsg"] = "账号或密码错误";
        }
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
    }
    conn->send(response.dump());
}

// 注册
void OceanIMService::regist(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do regist service!\n");
    nlohmann::json response;
    try
    {
        std::string name = js["name"];
        std::string password = js["password"];
        User user;
        user.setName(name);
        user.setPassword(password);
        bool state = _userModel.insert(user);

        if (state)
        {
            // 注册成功
            response["msgcate"] = REGIST_MSG_ACK;
            response["id"] = user.getId();
            response["errno"] = 0;
        }
        else
        {
            // 注册失败
            response["msgcate"] = REGIST_MSG_ACK;
            response["errno"] = 1;
            response["errmsg"] = "注册失败";
        }
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
    }
    conn->send(response.dump()); // 返回消息
}

// 请求参数异常
void OceanIMService::errreq(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    LOG_ERROR << "请求参数异常";
    nlohmann::json response;
    response["errno"] = 999;
    response["errmsg"] = "请求参数异常";
    conn->send(response.dump());
}

// 处理好友请求逻辑
void OceanIMService::addFriend(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do addFriend service!\n");
    std::map<int, std::string> states = {{SEND, "send"}, {ACCEPT, "accept"}, {REFUSE, "refuse"}, {IGNORE, "ignore"}};
    try
    {
        int optype = js["optype"].get<int>();
        int toid = js["to"].get<int>();
        int fromid = js["from"].get<int>();
        switch (optype)
        {
        case SEND:
        {
            FriendReq temp;
            temp.setFromId(fromid);
            temp.setToId(toid);
            _friendReqModel.insert(temp);

            { // 该部分作用域，可以并发执行
                std::lock_guard<std::mutex> lock(_connMutex);
                auto it = _userConnMap.find(toid);
                if (it != _userConnMap.end()) // 在_userConnMap找到这个用户
                {
                    // toid在线,转发消息
                    it->second->send(js.dump());
                    return;
                }
            }
            break;
        }
        case ACCEPT:
        {
            std::string state = states.at(optype);
            _friendReqModel.update(toid, state);
            Friend temp;
            temp.setUserId(toid);
            temp.setFriendId(fromid);
            _friendModel.insert(temp);

            temp.setUserId(fromid);
            temp.setFriendId(toid);
            _friendModel.insert(temp);

            { // 该部分作用域，可以并发执行
                std::lock_guard<std::mutex> lock(_connMutex);
                auto it = _userConnMap.find(fromid);
                if (it != _userConnMap.end()) // 在_userConnMap找到这个用户
                {
                    // toid在线,转发消息
                    it->second->send(js.dump());
                    return;
                }
            }
            break;
        }

        default:
        {
            std::string state = states.at(optype);
            _friendReqModel.update(toid, state);
            { // 该部分作用域，可以并发执行
                std::lock_guard<std::mutex> lock(_connMutex);
                auto it = _userConnMap.find(fromid);
                if (it != _userConnMap.end()) // 在_userConnMap找到这个用户
                {
                    // toid在线,转发消息
                    it->second->send(js.dump());
                    return;
                }
            }
            break;
        }
        }
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        nlohmann::json response;
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
        conn->send(response.dump()); // 返回消息
    }
}

// 一对一聊天
void OceanIMService::oneChat(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do oneChat service!\n");
    nlohmann::json response;
    try
    {
        int toid = js["to"].get<int>();
        int fromid = js["from"].get<int>();
        std::string msgtype = js["msgtype"];
        std::string message = js["message"];
        std::string readtype = "noread";
        OneChat temp;
        temp.setFromId(fromid);
        temp.setToId(toid);
        temp.setMsgType(msgtype);
        temp.setMessage(message);
        { // 该部分作用域，可以并发执行
            std::lock_guard<std::mutex> lock(_connMutex);
            auto it = _userConnMap.find(toid);
            if (it != _userConnMap.end()) // 在_userConnMap找到这个用户
            {
                // toid在线,转发消息
                it->second->send(js.dump());
                readtype = "read";
                return;
            }
        }
        temp.setReadType(readtype);
        _oneChatModel.insert(temp);
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
        conn->send(response.dump()); // 返回消息
    }
}

// 群聊天
void OceanIMService::groupChat(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do groupChat service!\n");
    nlohmann::json response;
}

// 创建群
void OceanIMService::createGroup(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do createGroup service!\n");
    nlohmann::json response;
    try
    {
        Group temp;
        temp.setGroupName(js["groupname"]);
        temp.setGroupDesc(js["groupdesc"]);
        bool state = _groupModel.createGroup(temp);
        if (state)
        {
            // 创建成功、
            response["msgcate"] = CREATE_GROUP_MSG_ACK;
            response["errno"] = 0;
            response["groupid"] = temp.getId();
            _groupModel.addGroup(js["userid"].get<int>(), temp.getId(), "creator");
        }
        else
        {
            // 创建失败
            response["msgcate"] = CREATE_GROUP_MSG_ACK;
            response["errno"] = 1;
            response["errmsg"] = "创建群失败";
        }
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        response["msgcate"] = CREATE_GROUP_MSG_ACK;
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
    }
    conn->send(response.dump()); // 返回消息
}

// 加入群
void OceanIMService::addGroup(const muduo::net::TcpConnectionPtr &conn, nlohmann::json &js, muduo::Timestamp &time)
{
    printf("do addGroup service!\n");
    nlohmann::json response;
    try
    {
        int userid = js["userid"].get<int>();
        int groupid = js["groupid"].get<int>();
        _groupModel.addGroup(userid, groupid, "normal");
        response["msgcate"] = ADD_GROUP_MSG_ACK;
        response["errno"] = 0;
        response["errmsg"] = "加群成功";
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what() << '\n';
        response["msgcate"] = ADD_GROUP_MSG_ACK;
        response["errno"] = 999;
        response["errmsg"] = "请求参数异常";
    }
    conn->send(response.dump()); // 返回消息
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

// 客户端异常退出
void OceanIMService::clientCloseException(const muduo::net::TcpConnectionPtr &conn)
{
    LOG_INFO << "客户端异常退出了！\n";
    User user;
    { // 加{}就表示作用域, 加锁解锁操作
        std::lock_guard<std::mutex> lock(_connMutex);

        for (auto it = _userConnMap.begin(); it != _userConnMap.end(); it++)
        {
            if (it->second == conn)
            {
                // 从map表删除用户的连接信息
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }
    if (user.getId() != -1) // 保护判断
    {
        printf("更新用状态为离线!");
        // 更新用户的状态信息
        user.setState("offline");
        _userModel.update(user);
    }
}

// 服务器异常后，业务状态的重置方法
void OceanIMService::reset()
{
    // 把online用户修改为offline
    _userModel.resetState();
}