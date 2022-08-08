/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 00:18:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 00:34:09
 * @FilePath: /c++/practices/chat_demo/src/common.h
 * @Description: 注释信息
 */

/** 只需要定义一个单独的函数被类成员函数调用即可，
 * 这个功能函数的作用就是提到的将文件描述符fd添加到epollfd标示的内核事件表中。
 * 因此我们将函数定义放在头文件 Common.h 中。
 * 除了这个功能函数之外，我们还需要把客户端和服务器端共用的宏定义放在 Common.h中，例如：
 * 1.服务器地址
 * 2.服务器端口号
 * 3.消息缓存大小
 * 4.服务器端默认的欢迎及退出消息
 **/

#ifndef CHAT_DEMO_COMMON_H
#define CHAT_DEMO_COMMON_H

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

// 默认服务器端IP地址
#define SERVER_IP "127.0.0.1"

// 服务器端口号
#define SERVER_PORT 8888

// int epoll_create(int size) 中的size
// 为epoll 支持的最大句柄数
#define EPOLLL_SIZE 5000

// 缓冲区大小65535
#define BUF_SIZE 0xFFFF

// 新用户登录后的欢迎信息
#define SERVER_MESSAGE "Welcome you join to the saltwater room -from:ocean.gzy!  Your chat ID: Client #%d"

// 其他用户收到的信息前缀
#define SERVER_MESSAGE "ClientID %d say >> %s"

// 退出系统
#define EXIT "EXIT"

// 提醒你是聊天室中的唯一客户
#define CAUTION "There is only you in the room!"

// 注册新的fd到epollfd中
// 参数enable_et表示 是否启用ET模式， 如果True则启用， 否则使用LT模式
static void addfd(int epollfd, int fd, bool enable_et)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (enable_et)
    {
        ev.events = EPOLLIN | EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    // 设置socket为 nonblocking模式
    // 执行完就转向下一条指令， 不管函数有没有返回
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
    printf("fd added to epoll!\n\n");
}

#endif