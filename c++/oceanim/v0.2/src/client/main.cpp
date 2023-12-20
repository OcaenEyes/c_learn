/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 08:54:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 11:54:57
 * @FilePath: /c++/oceanim/v0.2/src/client/main.cpp
 * @Description: 注释信息
 */
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "nlohmann/json.hpp"

#include "model/user.hpp"
#include "model/friend.hpp"
#include "model/friendreq.hpp"
#include "model/onechat.hpp"
#include "model/group.hpp"
#include "model/groupchat.hpp"

#include "common/common.h"
#include <functional>
#include <fstream>

// 记录当前系统登录的用户信息
User g_currentUser;

// 记录当前登录用户的好友列表信息
std::vector<User> g_currentUserFriends;

// 记录当前登录用户的群组列表信息
std::vector<Group> g_currentUserGroups;

// 操作指令
void help(int fd = 0, std::string str = "");
void onechat(int, std::string);
void sfriendreq(int, std::string);
void dfriendreq(int, std::string);
void addgroup(int, std::string);
void creategroup(int, std::string);
void groupchat(int, std::string);
void logout(int, std::string);
void quit(int fd = 0, std::string str = "");

// 打印显示用户信息
void showCurrentUserData();

// 显示主界面
void mainMenu(int clientfd);

// 获取系统时间（聊天信息需要增加时间戳）
std::string getCurrentTime()
{
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *ptm = localtime(&tt);
    char date[60] = {0};
    sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
            (int)ptm->tm_year + 1900,
            (int)ptm->tm_mon + 1,
            (int)ptm->tm_mday,
            (int)ptm->tm_hour,
            (int)ptm->tm_min,
            (int)ptm->tm_sec);
    return std::string(date);
}

// 注册系统支持的客户端命令列表
std::unordered_map<std::string, std::string> commandMap = {
    {"【显示所有支持的命令】help: ", "【输入】help"},
    {"【一对一聊天】chat:         ", "【输入】chat:friendid:message"},
    {"【发送好友请求】sfriendreq: ", "【输入】sfriendreq:friendid"},
    {"【处理好友请求】dfriendreq: ", "【输入】dfriendreq:friendid:dealtype"},
    {"【加入群】addgroup:         ", "【输入】addgroup:groupid"},
    {"【创建群】creategroup:     ", "【输入】creategroup:groupname:groupdesc"},
    {"【群聊天】groupchat:        ", "【输入】groupchat:groupid:message"},
    // {"【退出登录】logout:         ", "【输入】logout"},
    {"【退出应用程序】quit:       ", "【输入】quit"},
};

// 注册系统支持的客户端命令处理
std::unordered_map<std::string, std::function<void(int, std::string)>> commandHandlerMap = {
    {"help", help},
    {"chat", onechat},
    {"sfriendreq", sfriendreq},
    {"dfriendreq", dfriendreq},
    {"addgroup", addgroup},
    {"creategroup", creategroup},
    {"groupchat", groupchat},
    {"logout", logout},
    {"quit", quit}};

// 打印banner
void prtinBanner()
{
    std::ifstream inFile("./banner.txt");
    std::string str;
    while (inFile.good())
    {
        getline(inFile, str);
        printf("\033[0m\033[1;32m%s\033[0m", str.c_str());
        std::cout << "\n";
    }
}

// 显示当前登录用户的基本信息
void showCurrentUserData()
{
    std::cout << "=====================当前登录用户===================\n";
    printf("\033[0m\033[1;31m%s%d%s%s\n\033[0m", "【用户ID】:", g_currentUser.getId(), "    【昵称】:", g_currentUser.getName().c_str());

    std::cout << "=====================好友列表========================\n";
    if (!g_currentUserFriends.empty())
    {
        for (auto &&i : g_currentUserFriends)
        {
            std::cout << "【好友ID】:" << i.getId() << "    【昵称】:" << i.getName() << "    【状态】:" << i.getState() << "\n";
        }
    }

    std::cout << "=====================群列表============================\n";
    if (!g_currentUserGroups.empty())
    {
        for (auto &&i : g_currentUserGroups)
        {
            std::cout << "*********************\n";
            std::cout << "【群】:" << i.getId() << "    【群名称】:" << i.getGroupName() << "    【群介绍】:" << i.getGroupDesc() << "\n";
            for (auto &&j : i.getGroupUsers())
            {
                std::cout << "【用户ID】:" << j.getId() << "    【昵称】:" << j.getName() << "    【状态】:" << j.getState() << "    【角色】:" << j.getRole() << "\n";
            }
        }
    }
    std::cout << "=======================================================\n";
}

// 接收线程
void readTaskHandler(int clientfd)
{
    for (;;)
    {
        char buffer[1024] = {0};
        int ret = recv(clientfd, buffer, 1024, 0);
        if (ret == -1 || ret == 0)
        {
            close(clientfd);
            exit(-1);
        }

        nlohmann::json temp = nlohmann::json::parse(buffer);
        if (ONE_CHAT_MSG == temp["msgcate"].get<int>())
        {
            std::cout
                << "【" << temp["sendtime"].get<std::string>() << "】"
                << "【用户" << temp["fromname"] << "】"
                << ":" << temp["message"].get<std::string>() << "\n";
            continue;
        }

        if (GROUP_CHAT_MSG == temp["msgcate"].get<int>())
        {
            std::cout << "【" << temp["sendtime"].get<std::string>() << "】"
                      << "【群" << temp["groupid"] << "-"
                      << "用户" << temp["fromname"] << "】"
                      << ":" << temp["message"].get<std::string>() << "\n";
            continue;
        }

        if (FRIEND_REQ_RES == temp["msgcate"].get<int>())
        {
            std::cout << "【用户" << temp["from"] << "】发来一个好友添加请求\n";
            continue;
        }
    }
}

// help 命令
void help(int, std::string)
{
    std::cout << "**** 快捷操作指令-->可参考右侧输入的格式提示 ***\n";
    for (auto &&i : commandMap)
    {
        printf("\033[0m\033[1;33m%s  %s\033[0m", i.first.c_str(), i.second.c_str());
        std::cout << "\n";
    }
}

// 单聊命令
void onechat(int clienfd, std::string str)
{
    int idx = str.find(":");
    if (idx == -1)
    {
        std::cerr << "无效的命令输入！\n";
        return;
    }

    int friendid = atoi(str.substr(0, idx).c_str());
    std::string message = str.substr(idx + 1, str.size() - idx);

    // {"msgcate":3,"from":2,"fromname":"酸奶","to":1,"msgtype":"text","message":"hello,gzy","sendtime":""}
    nlohmann::json sendjs;
    sendjs["msgcate"] = ONE_CHAT_MSG;
    sendjs["from"] = g_currentUser.getId();
    sendjs["fromname"] = g_currentUser.getName();
    sendjs["to"] = friendid;
    sendjs["msgtype"] = "text";
    sendjs["message"] = message;
    sendjs["sendtime"] = "";

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 发送好友请求
void sfriendreq(int clienfd, std::string str)
{
    int friendid = atoi(str.c_str());
    // {"msgcate":5,"from":1,"fromname":"gzy","to":2,"optype":0} --发送请求
    nlohmann::json sendjs;
    sendjs["msgcate"] = FRIEND_REQ_RES;
    sendjs["from"] = g_currentUser.getId();
    sendjs["fromname"] = g_currentUser.getName();
    sendjs["to"] = friendid;
    sendjs["optype"] = SEND;

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 处理好友请求
void dfriendreq(int clienfd, std::string str)
{
    int idx = str.find(":");
    if (idx == -1)
    {
        std::cerr << "无效的命令输入！\n";
        return;
    }
    int friendid = atoi(str.substr(0, idx).c_str());
    int optype = atoi(str.substr(idx + 1, str.size() - idx).c_str());

    // {"msgcate":5,"from":1,"fromname":"gzy","to":2,"optype":1} --接受请求
    nlohmann::json sendjs;
    sendjs["msgcate"] = FRIEND_REQ_RES;
    sendjs["from"] = g_currentUser.getId();
    sendjs["fromname"] = g_currentUser.getName();
    sendjs["to"] = friendid;
    sendjs["optype"] = optype;

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 加入群
void addgroup(int clienfd, std::string str)
{
    int groupid = atoi(str.c_str());

    // {"msgcate":7,"userid":2,"groupid":1}
    nlohmann::json sendjs;
    sendjs["msgcate"] = ADD_GROUP_MSG;
    sendjs["userid"] = g_currentUser.getId();
    sendjs["groupid"] = groupid;

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 创建群
void creategroup(int clienfd, std::string str)
{
    int idx = str.find(":");
    if (idx == -1)
    {
        std::cerr << "无效的命令输入！\n";
        return;
    }
    std::string groupname = str.substr(0, idx).c_str();
    std::string groupdesc = str.substr(idx + 1, str.size() - idx);

    // {"msgcate":6,"userid":1,"groupname":"读书城南","groupdesc":"符读书城南"}
    nlohmann::json sendjs;
    sendjs["msgcate"] = CREATE_GROUP_MSG;
    sendjs["userid"] = g_currentUser.getId();
    sendjs["groupname"] = groupname;
    sendjs["groupdesc"] = groupdesc;

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 群聊
void groupchat(int clienfd, std::string str)
{
    int idx = str.find(":");
    if (idx == -1)
    {
        std::cerr << "无效的命令输入！\n";
        return;
    }
    int groupid = atoi(str.substr(0, idx).c_str());
    std::string message = str.substr(idx + 1, str.size() - idx);

    // {"msgcate":4,"id":-1,"toid":-1,"fromid":1,"groupid":1,"fromname":"gzy","msgtype":"text","message":"hello我是GZY","sendtime":""}
    nlohmann::json sendjs;
    sendjs["msgcate"] = GROUP_CHAT_MSG;
    sendjs["id"] = -1;
    sendjs["toid"] = -1;
    sendjs["fromid"] = g_currentUser.getId();
    sendjs["groupid"] = groupid;
    sendjs["fromname"] = g_currentUser.getName();
    sendjs["msgtype"] = "text";
    sendjs["message"] = message;
    sendjs["sendtime"] = "";

    std::string sendBuf = sendjs.dump();
    int ret = send(clienfd, sendBuf.c_str(), sendBuf.size() + 1, 0);
    if (ret == -1)
    {
        std::cerr << "发送消息失败\n";
    }
}

// 退出登录
void logout(int clienfd, std::string str)
{
}

// 退出程序
void quit(int fd, std::string str)
{
    exit(0);
}

// 主页聊天页面程序
void mainMenu(int clientfd)
{
    help();
    char buffer[1024] = {0};
    for (;;)
    {
        std::cin.getline(buffer, 1024);
        std::string commandBuf(buffer);

        std::string command; // 存储操作命令
        int idx = commandBuf.find(":");
        if (-1 == idx)
        {
            command = commandBuf;
        }
        else
        {
            command = commandBuf.substr(0, idx);
        }

        auto it = commandHandlerMap.find(command);
        if (it == commandHandlerMap.end())
        {
            std::cerr << "无效的命令输入！\n";
            continue;
        }

        // 调用相应的命令时间处理回调， mainMenu对修改封闭，添加新功能也不修改此处函数
        it->second(clientfd, commandBuf.substr(idx + 1, commandBuf.size() - idx));
    }
}

// 聊天客户端的时间，main线程用户发送线程， 子线程用作接收线程
int main(int argc, char **argv)
{
    prtinBanner();
    // if (argc < 3)
    // {
    //     std::cerr << "执行错误,需要ip地址 和port端口\n";
    //     exit(-1);
    // }

    // 解析参数中的ip和port
    // char *ip = argv[1];
    // uint16_t port = atoi(argv[2]);
    char ip[20] = {0};
    sprintf(ip, "127.0.0.1");
    uint16_t port = 12345;

    // 创建client端端socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cerr << "创建clienfd socket失败\n";
        exit(-1);
    }

    // 填写 client需要连接的server信息ip+port
    sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // client连接server
    if (-1 == connect(clientfd, (sockaddr *)&server, sizeof(server)))
    {
        std::cerr << "连接服务器失败\n";
        close(clientfd);
        exit(-1);
    }

    // main线程用于接收用户的键盘输入，负责发送数据
    for (;;)
    {
        // 显示首页面菜单: 登录、注册、退出
        std::cout << "===========================\n";
        std::cout << "      欢迎使用OCEAN IM      \n";
        std::cout << "\n";
        std::cout << "1.登录      \n";
        std::cout << "2.注册      \n";
        std::cout << "3.退出      \n";
        std::cout << "===========================\n";
        std::cout << "请选择要执行的操作,可输入序号数字:1或2或3\n";
        int choice = 0;
        std::cin >> choice;
        std::cin.get(); // 读掉缓冲区残留的回车

        switch (choice)
        {
        case 1:
        { // 登录
            char name[50] = {0};
            char pwd[50] = {0};
            std::cout << "用户昵称:";
            std::cin.getline(name, 50); // 读取整行

            std::cout << "密码:";
            std::cin >> pwd;
            std::cin.get();

            nlohmann::json js;
            js["name"] = name;
            js["password"] = pwd;
            js["msgcate"] = LOGIN_MSG;

            std::string req = js.dump();
            int ret = send(clientfd, req.c_str(), strlen(req.c_str()) + 1, 0);
            if (ret == -1)
            {
                std::cerr << "发送登录消息失败\n";
            }
            else
            {
                char buffer[65535] = {0};
                ret = recv(clientfd, buffer, 65535, 0);
                if (ret == -1)
                {
                    std::cerr << "读取登录响应消息失败\n";
                }
                else
                {
                    nlohmann::json res = nlohmann::json::parse(buffer);
                    // std::cout << "登录后的服务器响应:" << res.dump() << "\n";
                    if (res["errno"] == 0)
                    {
                        // 登录成功
                        // 记录登录用户的ID、名称
                        g_currentUser.setId(res["id"]);
                        g_currentUser.setName(res["name"]);

                        // 记录当前用户的好友列表信息
                        if (res.contains("friends"))
                        {
                            // std::cout << "查到了好友信息\n";
                            Friend::from_json(res, g_currentUserFriends);
                        }

                        // 记录当前用户的群组信息
                        if (res.contains("groups"))
                        {
                            // std::cout << "查到了群组信息\n";
                            Group::from_json(res, g_currentUserGroups);
                        }

                        // 显示当前用户基本信息、好友列表、群组列表
                        showCurrentUserData();

                        // 判断用户是否有未读的单聊消息
                        if (res.contains("onechats"))
                        {
                            // std::cout << "查到了单聊信息\n";
                            std::cout << "---------单聊消息-------\n";
                            // std::cout << res["onechats"] << "\n";
                            std::vector<OneChat> temp;
                            OneChat::from_json(res, temp);
                            for (auto &&i : temp)
                            {
                                std::cout
                                    << "【" << i.getSendTime() << "】"
                                    << "【用户" << i.getFromName() << "】"
                                    << ":" << i.getMessage() << "\n";
                            }
                        }

                        // 判断用户是否有群聊消息
                        if (res.contains("groupchats"))
                        {
                            // std::cout << "查到了群聊信息\n";
                            std::cout << "---------群聊消息-------\n";
                            std::vector<GroupChat> temp;
                            GroupChat::from_json(res, temp);
                            for (auto &&i : temp)
                            {
                                std::cout << "【" << i.getSendTime() << "】"
                                          << "【群" << i.getGroupId() << "-"
                                          << "用户" << i.getFromName() << "】"
                                          << ":" << i.getMessage() << "\n";
                            }
                        }

                        std::cout << "=======================================================\n";

                        // 登录成功后，启动线程负责接收数据
                        std::thread readTask(readTaskHandler, clientfd); // 创建线程对象，并设置线程函数，及线程函数参数
                        readTask.detach();

                        // 进入主菜单
                        mainMenu(clientfd);
                    }

                    else
                    {
                        // 登录失败
                        std::cerr << "登录失败" << res["errmsg"] << "\n";
                    }
                }
            }

            break;
        }
        case 2:
        { // 注册

            char name[50] = {0};
            char pwd[50] = {0};

            std::cout << "用户昵称:";
            std::cin.getline(name, 50); // 读取整行

            std::cout << "密码:";
            std::cin.getline(pwd, 50);

            nlohmann::json js;
            js["name"] = name;
            js["password"] = pwd;
            js["msgcate"] = REGIST_MSG;
            std::string req = js.dump();

            int ret = send(clientfd, req.c_str(), strlen(req.c_str()) + 1, 0);
            if (ret == -1)
            {
                std::cerr << "发送注册消息失败\n";
            }
            else
            {
                char buffer[1024] = {0};
                ret = recv(clientfd, buffer, 1024, 0);
                if (ret == -1)
                {
                    std::cerr << "读取注册响应消息失败\n";
                }
                else
                {
                    nlohmann::json res = nlohmann::json::parse(buffer);
                    if (res["errno"] == 0)
                    {
                        // 注册成功
                        std::cout << "注册成功! 您的用户ID是: " << res["id"] << "\n";
                    }
                    else
                    {
                        // 注册失败
                        std::cerr << "注册失败\n";
                    }
                }
            }

            break;
        }
        case 3: // 退出
            close(clientfd);
            exit(0);
            break;

        default:

            std::cerr << "错误的输入\n";
            break;
        }
    }

    return 0;
}