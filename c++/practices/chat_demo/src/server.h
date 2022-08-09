/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 00:35:25
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 21:26:16
 * @FilePath: /c++/practices/chat_demo/src/server.h
 * @Description: 注释信息
 */
#ifndef CHAT_DEMO_SERVER_H
#define CHAT_DEMO_SERVER_H

#include <cstring>
#include <iostream>
#include<list>
#include "common.h"

class server
{
private:
    // 广播消息给所有客户端
    int send_broadcast_message(int clientfd);

    // 服务器端 serverAddr信息
    struct sockaddr_in serverAddr;

    // 创建监听的socket
    int listener;

    // epoll_create创建后的返回值
    int epfd;

    // 客户端列表
    std::list<int> clients_list;

public:
    server(/* args */);
    ~server();

    // 初始化服务器端设置
    void init_server();

    // 关闭服务
    void close_server();

    // 开启服务
    void start_server();
};

#endif