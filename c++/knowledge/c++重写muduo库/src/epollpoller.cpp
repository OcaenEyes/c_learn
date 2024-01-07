/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 10:40:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-07 04:48:30
 * @FilePath: /c++/knowledge/c++重写muduo库/src/epollpoller.cpp
 * @Description: 注释信息
 */
#include "epollpoller.h"
#include "logger.h"
#include "channel.h"
#include "eventloop.h"
#include "poller.h"
#include "timestamp.h"

#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <strings.h>

namespace ocean_muduo
{
    // channel 未添加到poller的中
    const int k_new = -1; // channel的成员index_=-1
    // channel 已添加到poller中
    const int k_add = 1;
    // channel 从poller中删除
    const int k_del = 2;

    epollpoller::epollpoller(eventloop *loop)
        : poller(loop),
          epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
          events_(k_init_event_list_size)
    {
        if (epollfd_ == -1)
        {
            LOG_FATAL("epoll create failed,errno:%d", errno);
        }
    }

    epollpoller::~epollpoller()
    {
        ::close(epollfd_);
    }
    timestamp epollpoller::poll(int timeout_ms, channels *active_channels)
    {
        return timestamp();
    }

    // channel update ,remove  通过 eventloop 的update_channel、remove_channel,来调用poller的update_channel、remove_channel, 然后再调用 epollpoller的update_channel、remove_channel
    void epollpoller::update_channel(channel *chanl)
    {
    }
    void epollpoller::remove_channel(channel *chanl)
    {
    }
} // namespace ocean_muduo
