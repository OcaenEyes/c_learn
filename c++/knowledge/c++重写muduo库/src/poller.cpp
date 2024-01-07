/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-06 16:22:30
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-06 16:48:03
 * @FilePath: /c++/knowledge/c++重写muduo库/src/poller.cpp
 * @Description: 注释信息
 */
#include "poller.h"
#include "channel.h"
#include "eventloop.h"
#include "logger.h"

namespace ocean_muduo
{
    poller::poller(eventloop *loop) : loop_(loop)
    {
    }

    poller::~poller()
    {
    }

    bool poller::has_channel(channel *chanl) const
    {
        auto it = channel_map_.find(chanl->fd());
        return it != channel_map_.end() && it->second == chanl;
    }

} // namespace ocean_muduo
