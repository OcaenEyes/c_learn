/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 10:40:08
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 08:21:56
 * @FilePath: /c++/knowledge/c++重写muduo库/include/epollpoller.h
 * @Description: 注释信息
 */
#pragma once

#include "poller.h"
#include <sys/epoll.h>

namespace ocean_muduo
{
    /**
     * @brief
     *  epoll的使用
     *      1. epoll_create
     *      2. epoll_ctl    add、modify、delete
     *      3. epoll_wait
     *
     */
    class epollpoller : public poller
    {

    public:
        epollpoller(eventloop *loop);
        ~epollpoller() override;

        /**重写基类poller的抽象方法*/
        //  poll 对应 epoll_wait
        timestamp poll(int timeout_ms, channels *active_channels) override;
        //  update_channel、remove_channel 对应的 epoll_ctl行为
        void update_channel(channel *chanl) override;
        void remove_channel(channel *chanl) override;

    private:
        using eventlist = std::vector<epoll_event>;

        int epollfd_;      // epoll文件描述符
        eventlist events_; // 用于存放就绪事件

        static const int k_init_event_list_size = 16;

        // 填写活跃连接
        void fill_active_channels(int num_events, channels *active_channels) const;

        // 更新channel通道
        void update(int operation, channel *chanl);
    };

} // namespace ocean_muduo
