/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 10:40:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-07 11:50:37
 * @FilePath: /c++/knowledge/c++重写muduo库/src/epollpoller.cpp
 * @Description: 注释信息
 */
#include "epollpoller.h"
#include "logger.h"

#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <strings.h>

namespace ocean_muduo
{
    const int k_new = -1;
    const int k_add = 1;
    const int k_del = 2;

    epollpoller::epollpoller(eventloop *loop)
        : poller(loop),
          epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
          events_(k_init_event_list_size) {}

    epollpoller::~epollpoller()
    {
        ::close(epollfd_);
    }
} // namespace ocean_muduo
