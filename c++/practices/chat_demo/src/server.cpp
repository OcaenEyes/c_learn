/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 00:37:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 00:42:17
 * @FilePath: /c++/practices/chat_demo/src/server.cpp
 * @Description: 注释信息
 */
#include "server.h"

server::server(/* args */)
{
    // 初始化服务器地址和端口
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 初始化socket
    listener = 0;

    // epoll fd
    epfd = 0;
}

server::~server()
{
}