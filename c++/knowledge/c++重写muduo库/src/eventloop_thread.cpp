/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-09 09:57:28
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 12:06:03
 * @FilePath: /c++/knowledge/c++重写muduo库/src/eventloop_thread.cpp
 * @Description: 注释信息
 */
#include "eventloop_thread.h"
#include "eventloop.h"

#include <memory>

namespace ocean_muduo
{
    eventloop_thread::eventloop_thread(const std::function<void(eventloop *)> &cb, const std::string &name)
        : loop_(nullptr),
          exiting_(false),
          thread_(std::bind(&eventloop_thread::thread_func, this), name),
          mutex_(),
          cond_(),
          callback_(cb)
    {
    }

    eventloop_thread::~eventloop_thread()
    {
        exiting_ = true;
        if (loop_ != nullptr)
        {
            loop_->quit();  // 把线程内绑定的时间循环也退出
            thread_.join(); // 等待子线程结束
        }
    }

    // 启动循环
    eventloop *eventloop_thread::start_loop()
    {
        thread_.start(); // 启动底层的新线程

        eventloop *loop = nullptr;

        {
            std::unique_lock<std::mutex> lock(mutex_);
            while (loop == nullptr)
            {
                cond_.wait(lock);
            }
            loop = loop_;
        }
        return loop;
    }

    // 在单独的新线程内执行，
    void eventloop_thread::thread_func()
    {
        // 创建一个独立的eventloop,  和上面的线程是一一对应的
        eventloop loop;
        if (callback_)
        {
            callback_(&loop); // 调用回调函数
        }
        {
            std::unique_lock<std::mutex> lock(mutex_);
            loop_ = &loop;
            cond_.notify_one();
        }

        loop.loop(); // eventloop loop  调用poller 的poll
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = nullptr;
    }
} // namespace ocean_muduo
