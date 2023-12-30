/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-29 14:44:13
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-29 15:21:55
 * @FilePath: /c++/knowledge/c++线程池/include/threadpool.h
 * @Description: 注释信息
 */
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include <functional>
#include "../include/common/public.hpp"

// 任务抽象基类
// 用户可以自定义任务类型， 从Task继承而来， 重写run方法，实现自定义任务处理

class Task
{
private:
    Result *result_; // 任务结果
public:
    Task(/* args */) : result_(nullptr) {}
    ~Task() {}

    void exec(); // 执行

    virtual Any run() = 0; // 任务处理方法， 子类必须重写
    // virtual Task *clone() = 0; // 创建当前任务的副本， 用于线程池调度

    void set_result(Result *result);
};

// 自定义线程类
class Thread
{
private:
    std::function<void()> func_; // 线程函数
public:
    // 线程函数对象类型
    // using ThreadFunc = std::function<void()>;

    // 构造
    Thread(std::function<void()> func); // Thread(ThreadFunc func);

    // 析构
    ~Thread();

    void start(); // 启动线程
};

// 线程池支持的模式
enum class ThreadPoolMode
{
    CACHED, // 线程数量可动态增长
    FIXED   // 固定数量线程
};

// 线程池类型
class ThreadPool
{
private:
    std::vector<std::unique_ptr<Thread>> threads_; // 线程容器【存放线程的指针】  std::unique_ptr 独享资源的智能指针
    ThreadPoolMode thread_pool_mode_;              // 线程池的模式
    int init_thread_num_;                          // 初始线程数量
    std::atomic_int thread_busy_num_;              // 线程忙数量
    std::atomic_int thread_alive_num_;             // 线程存活数量
    std::atomic_int thread_exit_num_;              // 线程退出数量
    std::atomic_int thread_idle_num_;              //  空闲线程数量

    std::queue<std::shared_ptr<Task>> task_queue_; // 任务队列【存放任务的指针】 ， 值类型是无法多态的； 但是使用Task裸指针,有可能会出现指针指向的任务对象被析构的情况【无法确保任务对象生命周期】， ===> 使用智能指针来实现，std::shared_ptr<Task>保持拉长对象生命周期 ，且可以自动释放资源 ;std::shared_ptr 共享资源的智能指针
    std::atomic_uint task_cnt_;                    // 任务数量【原子操作】
    int task_queue_max_threshold_;                 // 任务队列最大上限阈值

    std::mutex task_queue_mutex_;                 // 互斥锁 【保证任务队列的线程安全】
    std::condition_variable cond_task_not_full_;  // 条件变量【表示任务队列未满】
    std::condition_variable cond_task_not_empty_; // 条件变量【表示任务队列未空】

    int max_wait_time_; // 最大等待时间【秒】

    std::atomic_bool stop_;    // 停止标志【原子操作】
    std::atomic_bool running_; // 运行标志【原子操作】
    std::atomic_bool init_;    // 初始化标志【原子操作】
    std::atomic_bool exit_;    // 退出标志【原子操作】

    void thread_func(); // 线程函数

    bool check_pool_running() const; // 检查线程池是否在运行

public:
    ThreadPool(/* args */);
    ~ThreadPool();

    // 禁用拷贝构造
    ThreadPool(const ThreadPool &) = delete;
    // 禁用赋值
    ThreadPool &operator=(const ThreadPool &) = delete;

    void start(int num = 4);                        // 启动线程池， 在启动的时候填入初始化的线程数量，默认值是4
    void set_mode(ThreadPoolMode mode);             // 设置线程池的模式
    void set_task_queue_max_hold(int max_hold);     // 设置任务队列的最大上限阈值
    Result submit_task(std::shared_ptr<Task> task); // 提交任务到线程池 【智能指针的方式】
};

#endif