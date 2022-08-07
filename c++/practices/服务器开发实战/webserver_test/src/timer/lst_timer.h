/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-06 10:56:10
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-06 13:34:47
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
    void add_timer(util_timer *timer, util_timer *lst_head);
    util_timer *head;
    util_timer *tail;

public:
    lst_timer(/* args */);
    ~lst_timer();

    void add_timer(util_timer *timer);
    void adjust_timer(util_timer *timer);
    void del_timer(util_timer *timer);
    void tick();
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
    static int *u_pipefd;
    lst_timer m_timer_lst;
    static int u_epollfd;
    int m_TIMESLOT;

public:
    utils(/* args */);
    ~utils();

    void init(int timeslot);

    //对文件描述符设置为非阻塞
    int setnonblocking(int fd);

    //对内核事件表注册读事件， ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断的触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char *info);
};

void cb_func(client_data *user_data);

#endif