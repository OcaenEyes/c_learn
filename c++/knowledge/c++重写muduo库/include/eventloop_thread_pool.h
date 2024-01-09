/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-09 20:53:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 21:52:22
 * @FilePath: /c++/knowledge/c++重写muduo库/include/eventloop_thread_pool.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"

#include <functional>
#include <string>
#include <memory>
#include <vector>

namespace ocean_muduo
{
    class eventloop;
    class eventloop_thread;

    class eventloop_thread_pool : public noncopyable
    {

    public:
        // using ThreadInitCallback = std::function<void(eventloop *)>;

        eventloop_thread_pool(eventloop *base_loop, const std::string &name);
        ~eventloop_thread_pool();

        void set_thread_num(int num);

        void start(const std::function<void(eventloop *)> &cb = std::function<void(eventloop *)>());

        // 如果工作在多线程中， base_loop_默认以轮询的方式分配channel给subloop
        eventloop * get_next_loop();

        std::vector<eventloop *> get_all_loops();

        bool started() const;
        
        const std::string get_name() const;

    private:
        eventloop *base_loop_; // 用户创建的起始loop
        std::string name_;

        bool started_;
        int num_threads_;
        int next_;
        std::vector<std::unique_ptr<eventloop_thread>> threads_; // 所有事件线程
        std::vector<eventloop *> loops_;
    };

} // namespace ocean_muduo
