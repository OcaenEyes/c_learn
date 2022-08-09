/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 00:35:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 21:42:03
 * @FilePath: /c++/practices/chat_demo/src/client.h
 * @Description: 注释信息
 */
#ifndef CHAT_DEMO_CLIENT_H
#define CHAT_DEMO_CLIENT_H

#include <cstring>
#include <iostream>
#include "common.h"

class client
{
private:
    // 当前连接服务创建的socket
    int sock;

    // 当前进程ID
    int pid;

    // epoll_create 创建后的返回值
    int epfd;

    // 创建管道，其中fd[0]用于父进程读，fd[1]用于子进程写
    int pipe_fd[2];

    // 表示客户端是否正常工作
    bool isClientWork;

    // 聊天信息缓冲区
    char message[BUF_SIZE];

    // 用户连接的服务器 IP+ port
    struct sockaddr_in serverAddr;

public:
    client(/* args */);
    ~client();

    // 连接服务器
    void connect_sever();

    // 断开连接
    void close_connect();

    // 启动客户端
    void start_client();
};

#endif