/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 13:07:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-08 13:55:40
 * @FilePath: /c++/knowledge/c++重写muduo库/include/eventloop.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"
#include "timestamp.h"

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

namespace ocean_muduo
{
    class channel; // 类型前置声明
    class poller;  // 类型前置声明

    /**
     * @brief 事件循环类， 主要包含 channel（包含fd 和 感兴趣的事件）、poller(epoll的抽象)
     *   对应reactor模型的  反应堆
     *
     */
    class eventloop : public noncopyable
    {
    public:
        // using Functor = std::function<void()>;

        eventloop(/* args */);
        ~eventloop();
        // 开启事件循环
        void loop();
        // 退出事件循环
        void quit();

        timestamp poll_return_time() const;

        // 在当前loop中执行cb
        void run_in_loop(std::function<void()> cb);
        // 把cb放入队列中，唤醒loop所在的线程，执行cb
        void queue_in_loop(std::function<void()> cb);

        // 用来唤醒loop所在的线程
        void wakeup();

        // eventloop的方法，触发调用poller的方法
        void update_channel(channel *chanl);
        void remove_channel(channel *chanl);
        bool has_channel(channel *chanl);

        // 判断 eventloop对象是否在自己的线程里
        bool is_in_loopthread() const;

    private:
        void handle_read(); // wake up
        void do_pending_functors(); // 执行回调

    
        using channels = std::vector<channel *>;

        std::atomic_bool looping_; // 原子操作，通过CAS实现的
        std::atomic_bool quit_;    // 标识退出loop循环
        const pid_t thread_id_;    // 记录当前loop所在线程的id

        timestamp poll_return_time_; // poller返回发生时间的channels的时间点
        std::unique_ptr<poller> poller_;

        int wakeup_fd_; // 当eventloop获取一个新用户的channel， 通过轮询算法选择一个subloop,通过该成员唤醒subloop处理channel
        std::unique_ptr<channel> wakeup_channel_;

        channels active_channels_;
        // channel *current_active_channel_;

        std::atomic_bool calling_pengding_functors_;          // 标识当前loop是否有需要执行的回调操作
        std::vector<std::function<void()>> pending_functors_; // 使用vector 存储loop需要执行的所有的回调操作
        std::mutex mutex_;                                    // 互斥锁， 用来保护上面的vector容器的线程安全操作
    };
} // namespace ocean_muduo
