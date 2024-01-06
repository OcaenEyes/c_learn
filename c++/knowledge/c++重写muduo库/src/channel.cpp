/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-06 23:01:58
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-06 23:23:35
 * @FilePath: /c++/knowledge/c++重写muduo库/src/channel.cpp
 * @Description: 注释信息
 */
#include "channel.h"
#include "eventloop.h"
// #include "poller.h"
#include "logger.h"
#include "timestamp.h"

#include <sys/epoll.h>

namespace ocean_muduo
{
    const int channel::k_none_event_ = 0;
    const int channel::k_read_event_ = POLLIN | POLLPRI;
    const int channel::k_write_event_ = POLLOUT;

    // Eventloop: ChannelList Poller
    channel::channel(eventloop *loop, int fd)
        : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false)
    {
    }

    channel::~channel()
    {
    }

    //
    void channel::tie(const std::shared_ptr<void> &obj)
    {
        // 弱智能指针tie_ 观察 强智能指针obj
        tie_ = obj;
        tied_ = true;
    }

    // 当改变channel所表示fd的events事件后， update负责在poller里更改fd相应的事件epoll_ctl
    // eventloop 包含了 channel list， poller
    void channel::update()
    {
        // 通过channel所属的eventloop， 调用poller的相应方法，注册fd的events事件
        // loop_->update_channel(this);
    }

    // 在channel所属的eventloop中， 把当前的channel删除掉
    void channel::remove()
    {
        // loop_->remove_channel(this);W
    }

    // 处理事件
    void channel::handle_event(timestamp receive_time)
    {
        if (tied_)
        {
            std::shared_ptr<void> guard = tie_.lock(); // 提升为强智能指针
            if (guard)                                 // 如果提升成功
            {
                handle_event_with_guard(receive_time);
            }
        }
    }

    // 处理事件， 并带有保护
    // 根据poller通知的channel发生 的具体事件， 有channel负责调用具体的回调操作
    void channel::handle_event_with_guard(timestamp receive_time)
    {
        LOG_INFO("channel handle_event revents%d\n"
        , revents_);
        if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
        {
            if (close_callback_)
            {
                close_callback_();
            }
        }

        if (revents_ & EPOLLERR)
        {
            if (error_callback_)
            {
                error_callback_();
            }
        }

        if (revents_ & EPOLLIN)
        {
            if (read_callback_)
            {
                read_callback_(receive_time);
            }
        }

        if (revents_ & EPOLLOUT)
        {
            if (write_callback_)
            {
                write_callback_();
            }
        }
    }

} // namespace ocean_muduo
