/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-06 10:56:10
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-06 20:59:02
 * @FilePath: /c++/server_develop_practice/webserver_test/src/timer/lst_timer.h
 * @Description: 注释信息
 */
#ifndef LST_TIMER_H
#define LST_TIMER_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <cstring>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <time.h>

#include "../log/log.h"

class util_timer;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    util_timer *timer;
};

class lst_timer
{
private:
    /* data */
public:
    lst_timer(/* args */);
    ~lst_timer();
};

class util_timer
{
private:
    /* data */
public:
    util_timer(/* args */);
    util_timer() : prev(NULL), next(NULL){};
    ~util_timer();

public:
    time_t expire;                  //定时器生效的绝对时间
    void (*cb_func)(client_data *); //定时器的回调函数
    util_timer *prev;
    util_timer *next;
};

class utils
{
private:
    /* data */
public:
    utils(/* args */);
    ~utils();
};

#endif