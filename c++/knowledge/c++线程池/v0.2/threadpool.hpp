/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-02 07:21:54
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-02 12:01:51
 * @FilePath: /c++/knowledge/c++线程池/v0.2/threadpool.hpp
 * @Description: 重构版本的线程池
 */
#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include <functional>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <future>
#include <thread>
#include <iostream>

const int TASK_MAX_THRESHOLD = 4;
const int THREAD_MAX_THRESHOLD = 10;
const int THREAD_MAX_IDLE_TIME = 10; // 10s空闲时间【线程最大空闲时间】

// 线程池支持的模式
enum class ThreadPoolMode
{
    MODE_FIXED,  // 固定大小线程池
    MODE_CACHED, // 动态调整数量的线程池
};

// 线程类
class Thread
{
public:
    // 线程函数对象类型
    //  using ThreadFunc = std::function<void(int)>;

    // 线程构造
    Thread(std::function<void(int)> func) : func_(std::move(func)),
                                            thread_id_(generate_id_++)
    {
        std::cout << "Thread: " << thread_id_ << " is created." << std::endl;
    }
    // 线程析构
    ~Thread() {}

    // 启动线程
    void start()
    {
        std::thread t(func_, thread_id_);
        t.detach();
    }

    // 获取线程ID
    int get_thread_id() { return thread_id_; }

private:
    std::function<void(int)> func_; // 线程函数
    int thread_id_;                 // 保存线程ID
    static int generate_id_;        // 静态成员变量 生成线程ID
};

// 线程池类
class ThreadPool
{
public:
    // 构造
    ThreadPool() : init_thread_num_(0),
                   task_cnt_(0),
                   idle_thread_num_(0),
                   current_thread_num_(0),
                   max_wait_time_(1),
                   max_thread_num_threshold_(THREAD_MAX_THRESHOLD),
                   max_task_queue_num_threshold_(TASK_MAX_THRESHOLD),
                   max_thread_idle_time_(THREAD_MAX_IDLE_TIME),
                   thread_pool_mode_(ThreadPoolMode::MODE_FIXED),
                   running_(false)
    {
    }
    // 析构
    ~ThreadPool()
    {
        running_ = false;

        // 等待线程池里面的线程返回， 有两种状态： 阻塞、正在执行任务中
        std::unique_lock<std::mutex> lock(task_queue_mutex_);
        cond_task_not_empty_.notify_all(); // 通知所有-->【当前任务还没有空】
        cond_exit_.wait(lock, [&]
                        { return threads_.empty(); }); // 等待线程容器变空
    }

    // 设置线程池工作模式
    void set_mode(ThreadPoolMode mode)
    {
        if (!check_pool_running())
        {
            return;
        }
        thread_pool_mode_ = mode;
    }

    // 启动线程池， 在启动的时候填入初始化的线程数量，默认值是硬件所支持的创建的线程数量
    void start(int num = std::thread::hardware_concurrency())
    {
        running_ = true;
        init_thread_num_ = num;
        current_thread_num_ = num;

        // 创建线程对象，并放入线程容器中
        std::unique_ptr<Thread> ptr(new Thread(std::bind(&ThreadPool::thread_func, this, std::placeholders::_1))); // 创建线程对象，并绑定【方式一】
        int thread_id = ptr->get_thread_id();
        threads_.emplace(thread_id, std::move(ptr)); // 在 C++11 之后，vector 容器中添加了新的方法：emplace_back() ，和 push_back() 一样的是都是在容器末尾添加一个新的元素进去，不同的是 emplace_back() 在效率上相比较于 push_back() 有了一定的提升。

        // 启动所有线程
        for (int i = 0; i < num; i++)
        {
            threads_[thread_id]->start(); // 启动线程
            idle_thread_num_++;           // 线程启动后，空闲线程++
        }
    }

    // 设置线程池在cached模式下 线程数量阈值
    void set_max_thread_num_threshold(int threshold)
    {
        if (!check_pool_running())
        {
            return;
        }
        if (thread_pool_mode_ == ThreadPoolMode::MODE_CACHED)
        {
            max_thread_num_threshold_ = threshold;
        }
    }

    // 设置线程池在cached模式下 线程最大空闲时间
    void set_max_thread_idle_time(int idle_time)
    {
        if (!check_pool_running())
        {
            return;
        }
        if (thread_pool_mode_ == ThreadPoolMode::MODE_CACHED)
        {
            max_thread_idle_time_ = idle_time;
        }
    }

    // 设置任务队列的最大上限阈值
    void set_max_task_queue_num_threshold(int threshold)
    {
        if (!check_pool_running())
        {
            return;
        }
        max_task_queue_num_threshold_ = threshold;
    }

    // 提交任务到线程池,并返回一个std::future对象
    // 返回值 std::future<类型>， 使用 std::result_of<Func(Args...)>::type获取对应的返回类型
    // 使用可变参模板编程， 让submit_task可以接受任意任务函数、和任意类型的参数
    // template<typename... _Args>，其实这个就是变参数模板，然后它的参数也是比较特别的_Args&&... __args
    template <typename Func, typename... Args>
    auto submit_task(Func &&func, Args &&...args) -> std::future<typename std::result_of<Func(Args...)>::type>
    {
        std::cout << "submit_task begin \n";
        using return_type = typename std::result_of<Func(Args...)>::type;
        // 创建一个智能指针task， std::packaged_task对象，并将任务函数和参数绑定到该对象上 [std::forward 保持左右值特性]
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        // 获取任务函数的返回值
        std::future<return_type> res = task.get_future();

        // 获取锁
        std::unique_lock<std::mutex> lock(task_queue_mutex_);

        // 线程通信，等待任务队列非满， 用户提交任务，最长不能阻塞超过1S，否则提交任务失败
        if (!cond_task_not_full_.wait_for(lock, std::chrono::seconds(1), [&]
                                          { return task_queue_.size() < max_task_queue_num_threshold_; }))
        {
            // cond_task_not_full_等待1S之后，条件仍然没有满足
            // 任务队列已满，提交任务失败
            std::cerr << "task queue is full, submit task failed!\n";
            auto res_null = std::make_shared<std::packaged_task<return_type()>>([]()
                                                                                { return return_type(); });
            return res_null.get_future();
        }

        // 任务队列非满,将任务添加到队列中
        //  通过指针解引用,触发执行任务
        task_queue_.emplace([task]()
                            { (*task)(); });
        task_cnt_++; // 任务数量++

        // 由于放入量新任务，此时任务队列不为空，则cond_task_not_empty_触发通知，赶快分配线程执行任务
        cond_task_not_empty_.notify_all();

        // 在cached模式下，任务处理比较急，小而快的任务，可以考虑根据任务数量适当增加线程数量
        if (thread_pool_mode_ == ThreadPoolMode::MODE_CACHED && task_cnt_ > idle_thread_num_ && current_thread_num_ < max_thread_num_threshold_)
        {
            // 触发创建新的新的线程
            std::cout << " cached mode: need create new thread\n";

            // 创建新的线程对象
            std::unique_ptr<Thread> ptr(new Thread(std::bind(&ThreadPool::thread_func, this, std::placeholders::_1)));
            // 获取线程ID
            int thread_id = ptr->get_thread_id();
            // 将新创建的线程对象添加到线程池中
            threads_.emplace(thread_id, std::move(ptr));

            // 启动线程
            threads_[thread_id]->start();

            idle_thread_num_++;    // 空闲线程数量++
            current_thread_num_++; // 当前线程数量++
        }

        return res; // 返回任务的结果
    }

    // template <class F, class... Args>
    // auto enqueue(F &&f, Args &&...args)
    //     -> std::future<typename std::result_of<F(Args...)>::type>;

    // 禁用拷贝构造
    ThreadPool(const ThreadPool &) = delete;
    // 禁用赋值重载
    ThreadPool &operator=(const ThreadPool &) = delete;

private:
    ThreadPoolMode thread_pool_mode_;                          // 线程池的模式
    std::unordered_map<int, std::unique_ptr<Thread>> threads_; // 线程容器
    std::atomic_bool running_;                                 // 线程池运行标志【原子操作】
    int init_thread_num_;                                      // 初始线程数量
    int max_thread_num_threshold_;                             // 最大线程数量
    std::atomic_int idle_thread_num_;                          // 空闲线程数量【原子操作】
    std::atomic_int current_thread_num_;                       // 当前累计线程数量【原子操作】
    int max_thread_idle_time_;                                 // 线程最大空闲时间
    int max_wait_time_;                                        // 最大等待时间[线程等待时间，信号量等待多少秒]

    std::queue<std::function<void()>> task_queue_; // 任务队列
    std::atomic_uint task_cnt_;                    // 任务数量【原子操作】
    int max_task_queue_num_threshold_;             // 任务队列最大上限阈值
    std::mutex task_queue_mutex_;                  // 互斥锁 【保证任务队列的线程安全】

    std::condition_variable cond_exit_;           // 退出条件变量【表示要退出线程池】
    std::condition_variable cond_task_not_full_;  // 条件变量【表示任务队列未满】
    std::condition_variable cond_task_not_empty_; // 条件变量【表示任务队列未空】

    bool check_pool_running() const // 检查线程池是否在运行
    {
        return running_ && threads_.size() > 0;
    }

    void thread_func(int thread_id) // 线程函数
    {
        // 当前时间
        auto last_time = std::chrono::high_resolution_clock::now();

        // 线程内部循环， 不断从任务队列中取出任务，并执行
        while (true) // 所有任务必须执行完成，线程池才能回收所有线程资源
        {
            // 从任务队列中取出任务 ，函数对象
            std::function<void()> task_;
            {
                // 获取锁
                std::unique_lock<std::mutex> lock(task_queue_mutex_);
                // cached模式下，有可能创建了很多线程； 但空闲时间超过了60s, 应把多余的线程结束回收掉（超过 初始数量的其他线程）
                // 当前时间 -  上一次线程执行的时间 >60S
                // 每秒返回一次，  需要区分：超时返回、任务执行返回
                while (task_queue_.empty())
                {
                    // 线程池运行结束
                    if (!check_pool_running())
                    {
                        threads_.erase(thread_id); // 将线程从线程池 移除
                        std::cout << "thread " << std::this_thread::get_id() << " exit\n";
                        cond_exit_.notify_all(); //
                        return;
                    }

                    // 如果线程池模式是 CACHED模式，需要考虑空闲线程回收的机制
                    if (thread_pool_mode_ == ThreadPoolMode::MODE_CACHED)
                    {
                        // 前提是任务队列不空，且线程等待任务超时， ===>相当于线程拿不到新的任务了
                        if (cond_task_not_empty_.wait_for(lock, std::chrono::seconds(max_wait_time_)) == std::cv_status::timeout)
                        {
                            auto now = std::chrono::high_resolution_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - last_time); // 判断线程函数从开始到现在的时间间隔
                            // 如果线程已经空闲超过 max_thread_idle_time_， 且当前总线程数量超过了初始线程量
                            if (duration.count() >= max_thread_idle_time_ && current_thread_num_ > init_thread_num_)
                            {
                                // 开始进行线程回收
                                threads_.erase(thread_id); // 将线程从线程池 移除
                                current_thread_num_--;     // 总线程数量--
                                idle_thread_num_--;        // 空闲线程数量--

                                std::cout << "thread:" << thread_id << " recycle\n";
                                return;
                            }
                        }
                    }

                    else
                    {
                        // 任务队列是空的时候， cond_task_not_empty_就一直等待 任务队列不为空的信号，即等待cond_task_not_empty_条件变量
                        cond_task_not_empty_.wait(lock, [&]() -> bool
                                                  { return !task_queue_.empty(); }); // 进入等待状态后释放锁; 等待直到cond_task_not_empty_条件变量满足
                    }
                }

                //  等到任务了
                std::cout << "thread:" << thread_id << " get task\n";
                idle_thread_num_--;  // 空闲线程数量--
                task_queue_.front(); // 任务队列不为空， 即cond_task_not_empty_条件变量满足， 将任务从任务队列中取出
                task_queue_.pop();   // 任务出队
                task_cnt_--;         // 任务数量--

                // 如果依然有剩余任务，则继续触发通知 其他的线程执行任务
                if (task_queue_.size() > 0)
                {
                    cond_task_not_empty_.notify_all(); // 通知其他线程执行任务
                }

                // 取出任务后，task_queue_就非满了， 通知可以继续提交任务
                cond_task_not_full_.notify_all();
            }
            if (task_ != nullptr)
            {
                task_(); // 执行std::function<void()>
            }

            // 任务执行完之后
            idle_thread_num_++;                                     // 空闲线程数量++
            last_time = std::chrono::high_resolution_clock().now(); // 更新线程执行完成的时间点【即新的空闲开始时间】
        }
    }
};

#endif