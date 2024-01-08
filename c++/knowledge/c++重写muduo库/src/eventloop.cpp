/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 13:08:31
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-08 08:55:06
 * @FilePath: /c++/knowledge/c++重写muduo库/src/eventloop.cpp
 * @Description: 注释信息
 */
#include "eventloop.h"
#include "channel.h"
#include "poll.h"
#include "epollpoller.h"
#include "currentthread.h"
#include "logger.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/eventfd.h>
#include <errno.h>

namespace ocean_muduo
{

    // 防止一个线程 创建多个eventloop
    __thread eventloop *t_loop_in_this_thread = nullptr;

    // 定义默认的poller IO复用接口的超时时间 毫秒
    const int k_poll_time_ms = 10000;

    // 创建wakeup_fd ,用来 notify通知 唤醒 subReactor来处理新来的channel
    int create_event_fd()
    {
        int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (evtfd < 0)
        {
            LOG_FATAL("eventfd error:%d\n", errno);
        }
        return evtfd;
    }

    eventloop::eventloop(/* args */)
        : looping_(false),
          quit_(false),
          calling_pengding_functors_(false),
          thread_id_(tid()),
          poller_(poller::new_default_poller(this)),
          wakeup_fd_(create_event_fd()),
          wakeup_channel_(new channel(this, wakeup_fd_)),
          current_active_channel_(nullptr)
    {
        LOG_DEBUG("eventloop created %p in thread %d \n", this, thread_id_);
        if (t_loop_in_this_thread)
        {
            LOG_FATAL("another eventloop %p exists in thread %d \n ", t_loop_in_this_thread, thread_id_);
        }
        else
        {
            t_loop_in_this_thread = this;
        }

        // 设置wakeupfd的事件类型 及发生事件后的回调操作
        wakeup_channel_->set_read_callback(std::bind(&eventloop::handle_read, this));

        // 每一个eventloop都将监听wakeup channel的EPOLLIN 读事件
        wakeup_channel_->enable_reading();
    }

    eventloop::~eventloop()
    {
        wakeup_channel_->disable_all(); // 对所有事件都不感兴趣
        wakeup_channel_->remove();
        ::close(wakeup_fd_);             // 关闭wakeup_fd_
        t_loop_in_this_thread = nullptr; // 回收资源
    }

    // 开启事件循环
    void eventloop::loop()
    {
        looping_ = true;
        quit_ = false;

        LOG_INFO("eventloop::loop(), %p start looping \n", this);
        while (!quit_)
        {
            /* code */
        }
    }

    void eventloop::quit()
    {
    }

    timestamp eventloop::poll_return_time() const
    {
        return poll_return_time_;
    }

    bool eventloop::is_in_loopthread() const
    {
        return thread_id_ == tid();
    }

    void eventloop::handle_read()
    {
        uint64_t one = 1;
        ssize_t n = read(wakeup_fd_, &one, sizeof(one));
        if (n != sizeof(one))
        {
            LOG_ERROR("eventloop::handle_read() reads %d bytes instead of 8.\n", n);
        }
    }

} // namespace ocean_muduo