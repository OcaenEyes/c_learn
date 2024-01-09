/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 13:08:31
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 08:23:53
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
          wakeup_channel_(new channel(this, wakeup_fd_))
    //   current_active_channel_(nullptr)
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
            active_channels_.clear();
            // 监听两类fd
            //  1. client的fd
            //  2. wakeup fd
            poll_return_time_ = poller_->poll(k_poll_time_ms, &active_channels_);
            for (auto &&i : active_channels_)
            {
                // poller 监听哪些channel发生事件了， 然后上报给eventloop，通知channel处理事件
                i->handle_event(poll_return_time_);
            }

            // 执行当前eventloop事件循环需要处理的回调操作
            /**
             * IO线程  mainloop accept fd ---- 已连接的channel subloop
             *  mainloop 事先注册一个回调cb， （需要subloop来执行）；
             *          wakeup唤醒subloop之后，执行下面的方法，（执行之前mainloop注册的回调cb）
             */
            do_pending_functors();
        }
        LOG_INFO("eventloop::loop(), %p stop looping \n", this);
        looping_ = false;
    }

    // 退出事件循环
    //  1. loop在自己的线程中调用quit()
    //  2. 在非loop的线程中， 调用loop的quit
    /**
     *               mainloop
     *
     *    subloop1     subloop2      subloop3
     */
    void eventloop::quit()
    {
        quit_ = true;
        if (!is_in_loopthread()) // 如果是在其他线程中，调用的quit ， 在一个subloop（worker）中，调用了mainloop（IO）的quit
        {
            wakeup();
        }
    }

    timestamp eventloop::poll_return_time() const
    {
        return poll_return_time_;
    }

    // 在当前loop中执行cb
    void eventloop::run_in_loop(std::function<void()> cb)
    {
        if (is_in_loopthread())
        { // 在当前的loop线程中执行cb
            cb();
        }
        else
        { // 在非当前线程loop中执行cb, 需要唤醒loop所在线程 执行cb
            queue_in_loop(cb);
        }
    }

    // 把cb放入队列中，唤醒loop所在线程，执行cb
    void eventloop::queue_in_loop(std::function<void()> cb)
    {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            pending_functors_.emplace_back(cb); // emplace_back直接构造； push_back拷贝构造
        }

        // 唤醒相应的， 需要执行上面回调操作的loop线程
        //  ||calling_pengding_functors_的含义 是当前loop正在指向回调， 但loop有了新回调
        if (!is_in_loopthread() || calling_pengding_functors_)
        {
            wakeup(); // 唤醒loop所在线程
        }
    }

    // 用来唤醒loop所在的线程的， 可以想wakeupfd_写一个数据, wakeup channe就会发生读事件， 当前loop所在线程就会被唤醒
    void eventloop::wakeup()
    {
        uint64_t one = 1;
        ssize_t n = write(wakeup_fd_, &one, sizeof(one));
        if (n != sizeof(one))
        {
            LOG_ERROR("eventloop::wakeup() write %ld bytes instead of 8.\n", n);
        }
    }

    // eventloop 的方法 ---> 调用poller的方法
    void eventloop::update_channel(channel *chanl)
    {
        poller_->update_channel(chanl);
    }

    void eventloop::remove_channel(channel *chanl)
    {
        poller_->remove_channel(chanl);
    }

    bool eventloop::has_channel(channel *chanl)
    {
        return poller_->has_channel(chanl);
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
            LOG_ERROR("eventloop::handle_read() reads %ld bytes instead of 8.\n", n);
        }
    }

    void eventloop::do_pending_functors() // 执行回调
    {
        std::vector<std::function<void()>> functors;
        calling_pengding_functors_ = true;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            functors.swap(pending_functors_);
        }

        for (auto &&i : functors)
        {
            i(); // 执行当前loop所要执行的回调操作
        }
        calling_pengding_functors_ = false;
    }

} // namespace ocean_muduo