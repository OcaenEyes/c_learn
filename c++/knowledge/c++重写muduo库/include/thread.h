/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-09 08:32:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 11:48:32
 * @FilePath: /c++/knowledge/c++重写muduo库/include/thread.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"

#include <functional>
#include <thread>
#include <memory>
#include <unistd.h>
#include <string>
#include <atomic>

namespace ocean_muduo
{
    class thread : public noncopyable
    {
    public:
        // 声明为explicit的构造函数不能在隐式转换中使用
        explicit thread(std::function<void()> func, const std::string &name = "");
        thread();
        ~thread();

        // using ThreadFuc = std::function<void()>;

        void start();

        void join();

        bool started() const;
        pid_t get_tid() const;
        const std::string &get_name() const;
        static int get_num_created();

    private:
        bool started_;
        bool joined_;
        std::shared_ptr<std::thread> thread_;
        pid_t tid_;
        std::function<void()> func_;
        std::string name_;

        static std::atomic_int num_created_;

        void set_default_name();
    };

} // namespace ocean_muduo
