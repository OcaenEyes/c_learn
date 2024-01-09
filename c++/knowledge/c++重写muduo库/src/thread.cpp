/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-09 21:59:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-09 21:59:37
 * @FilePath: /c++/knowledge/c++重写muduo库/src/thread.cpp
 * @Description: 注释信息
 */
#include "thread.h"
#include "currentthread.h"

#include <semaphore.h>

namespace ocean_muduo
{

    // 静态成员变量 需要在类外初始化
    std::atomic_int thread::num_created_(0);

    // 声明为explicit的构造函数不能在隐式转换中使用
    thread::thread(std::function<void()> func, const std::string &name)
        : name_(name),
          started_(false),
          joined_(false),
          tid_(0),
          func_(std::move(func))

    {
        set_default_name();
    }

    thread::thread()
    {
    }
    
    thread::~thread()
    {
        if (started_ && !joined_)
        {
            thread_->detach(); // 分离线程
        }
    }

    void thread::start() // 一个thread对象，记录的就是一个新线程的详细信息
    {
        started_ = true;

        sem_t sem;
        sem_init(&sem, false, 0);

        thread_ = std::shared_ptr<std::thread>(new std::thread([&]
                                                               {
            // 获取线程tid值
            tid_ = tid(); 
            sem_post(&sem); // 触发信号量

            // 开启一个新线程，专门执行该线程函数func_
            func_(); }));

        // 这里必须等待 ，获取到上面创建新线程处理的tid_值
        sem_wait(&sem); // 信号量杯post+1之后 ，这里会感知到结果
    }

    void thread::join()
    {
        joined_ = true;
        thread_->join();
    }

    bool thread::started() const
    {
        return started_;
    }

    pid_t thread::get_tid() const
    {
        return tid_;
    }

    const std::string &thread::get_name() const
    {
        return name_;
    }

    int thread::get_num_created()
    {
        return num_created_;
    }

    void thread::set_default_name()
    {
        int num = ++num_created_;
        if (name_.empty())
        {
            name_ = "thread_" + std::to_string(num);
        }
    }
} // namespace ocean_muduo
