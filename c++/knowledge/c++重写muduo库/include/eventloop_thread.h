#pragma once

#include "noncopyable.h"
#include "thread.h"

#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>

namespace ocean_muduo
{
    class eventloop;

    class eventloop_thread : public noncopyable
    {

    public:
        // using ThreadInitCallback = std::function<void(eventloop *)>;

        eventloop_thread(const std::function<void(eventloop *)> &cb = std::function<void(eventloop *)>(),
                         const std::string &name = "");
        ~eventloop_thread();

        // 开始循环
        eventloop *start_loop();

    private:
        eventloop *loop_;
        bool exiting_;
        thread thread_;
        std::mutex mutex_;
        std::condition_variable cond_;
        std::function<void(eventloop *)> callback_;

        void thread_func();
    };

} // namespace ocean_muduo
