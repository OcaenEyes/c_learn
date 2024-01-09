/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 10:40:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 08:22:05
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
#include <unistd.h>
#include <strings.h>
#include <string.h>

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
        // 实际应该是用debug模式
        LOG_INFO("func=%s => fd total cout %ld \n ", __FUNCTION__, channel_map_.size());

        // events_.begin() 首元素， *解引用， &再取址
        int num_events = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeout_ms);
        int temp_errno = errno;

        timestamp now(timestamp::now());
        if (num_events > 0)
        {
            // 实际应该是用debug模式
            LOG_INFO("func=%s =>  %d events happened \n ", __FUNCTION__, num_events);
            fill_active_channels(num_events, active_channels);

            if (num_events == events_.size())
            {
                events_.resize(events_.size() * 2);
            }
        }
        else if (num_events == 0)
        {
            // 实际应该是用debug模式
            LOG_INFO("func=%s =>  timeout! \n ", __FUNCTION__);
        }
        else
        {
            if (temp_errno != EINTR)
            {
                errno = temp_errno;
                LOG_ERROR("epollpoller::poll() err, errno:%d", errno);
            }
        }

        return now;
    }

    // channel update ,remove  通过 eventloop 的update_channel、remove_channel,来调用poller的update_channel、remove_channel, 然后再调用 epollpoller的update_channel、remove_channel
    /**
     * @brief
     *
     * @param chanl
     *
     *  eventloop
     *   1. channels_ [存放所有channel]
     *   2. poller
     *       2.1 channel_map_ : <fd,channel*>
     *
     */
    void epollpoller::update_channel(channel *chanl)
    {
        const int index = chanl->index();
        const int fd = chanl->fd();
        const int events = chanl->events();

        LOG_INFO("func= %s fd=%d events=%d index=%d \n", __FUNCTION__, fd, events, index);

        if (index == k_new || index == k_del) // chanl 未在poller上注册，或已删除
        {
            if (index == k_new)
            {
                channel_map_[fd] = chanl;
            }
            chanl->set_index(k_add);
            update(EPOLL_CTL_ADD, chanl);
        }
        else // chanl 已经在poller上注册过了
        {
            if (chanl->is_none_event())
            { // chanl已经对所有事件不感兴趣
                update(EPOLL_CTL_DEL, chanl);
                chanl->set_index(k_del);
            }
            else
            {
                update(EPOLL_CTL_MOD, chanl);
            }
        }
    }

    // 从poller中删除channel
    void epollpoller::remove_channel(channel *chanl)
    {
        LOG_INFO("func= %s fd=%d events=%d index=%d \n", __FUNCTION__, chanl->fd(), chanl->events(), chanl->index());

        int fd = chanl->fd();
        channel_map_.erase(fd);

        int index = chanl->index();

        if (index == k_add)
        {
            update(EPOLL_CTL_DEL, chanl);
        }
    }

    void epollpoller::fill_active_channels(int num_events, channels *active_channels) const
    {
        for (int i = 0; i < num_events; i++)
        {
            channel *chanl = static_cast<channel *>(events_[i].data.ptr);
            chanl->set_revents(events_[i].events);

            active_channels->push_back(chanl); // eventloop就拿到了他的poller给它返回的所有发生事件的channel列表了
        }
    }

    // 更新channel通道， epoll_ctl add/mod/del
    void epollpoller::update(int operation, channel *chanl)
    {
        int fd = chanl->fd();
        epoll_event event;
        bzero(&event, sizeof(event));

        event.events = chanl->events();
        event.data.fd = fd;
        event.data.ptr = chanl;

        // 更改fd上的事件
        int ret = ::epoll_ctl(epollfd_, operation, fd, &event);
        if (ret < 0) // 更改fd上事件的时候出错
        {
            if (operation == EPOLL_CTL_DEL)
            {
                LOG_ERROR("epoll ctl del error,errno:%d\n", errno);
            }
            else
            {
                LOG_FATAL("epoll ctl add/mod error,errno:%d\n", errno);
            }
        }
    }

} // namespace ocean_muduo
