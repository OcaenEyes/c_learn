/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-29 02:58:10
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-04 09:03:54
 * @FilePath: /c++/knowledge/c++线程池/v0.1/src/threadpool.cpp
 * @Description: 注释信息
 */
#include "../include/threadpool.h"
#include <iostream>
#include "threadpool.h"
// #include <functional>

const int TASK_MAX_THRESHOLD = 4;
const int THREAD_MAX_THRESHOLD = 10;
const int THREAD_MAX_IDLE_TIME = 10; // 60s空闲时间【线程最大空闲时间】

// 构造线程池
ThreadPool::ThreadPool() : init_thread_num_(0),
                           task_cnt_(0),
                           thread_idle_num_(0),
                           thread_current_num_(0),
                           max_wait_time_(1),
                           max_thread_num_(THREAD_MAX_THRESHOLD),
                           task_queue_max_threshold_(TASK_MAX_THRESHOLD),
                           thread_pool_mode_(ThreadPoolMode::FIXED),
                           max_thread_idle_time_(THREAD_MAX_IDLE_TIME),
                           running_(false)

{
}

// 析构线程池
ThreadPool::~ThreadPool()
{
    running_ = false;

    // 等待线程池里面所有线程返回，  有两种状态：阻塞、正在执行任务中
    std::unique_lock<std::mutex> lock(task_queue_mutex_);
    cond_task_not_empty_.notify_all(); // 唤醒所有线程
    cond_exit_.wait(lock, [&]
                    { return task_queue_.empty(); });
}

// 启动线程池
void ThreadPool::start(int num)
{
    std::cout << "ThreadPool start" << std::endl;
    // 设置线程池运行状态
    running_ = true;

    // 设置初始线程个数
    init_thread_num_ = num;
    thread_current_num_ = num;

    // 创建线程对象,并插入std::vector<Thread *> threads_;
    for (int i = 0; i < init_thread_num_; i++)
    {
        std::unique_ptr<Thread> ptr(new Thread(std::bind(&ThreadPool::thread_func, this, std::placeholders::_1))); // 创建线程对象，并绑定【方式一】
        // std::unique_ptr<Thread> ptr = std::make_unique<Thread>(std::bind(&ThreadPool::thread_func, this)); // 创建线程对象，并绑定;【方式二 】c++14之后才有

        int thread_id = ptr->get_thread_id();
        threads_.emplace(thread_id, std::move(ptr)); // 在 C++11 之后，vector 容器中添加了新的方法：emplace_back() ，和 push_back() 一样的是都是在容器末尾添加一个新的元素进去，不同的是 emplace_back() 在效率上相比较于 push_back() 有了一定的提升。
    }

    // 启动所有线程, 遍历std::vector<Thread *> threads_;执行
    for (int i = 0; i < init_thread_num_; i++)
    {
        threads_[i]->start();
        
        // 在启动线程后，就记录初始空闲线程数量
        thread_idle_num_++;
    }
}

// 检查线程池运行状态
bool ThreadPool::check_pool_running() const
{
    return running_;
}

// 设置线程池工作模式
void ThreadPool::set_mode(ThreadPoolMode mode)
{
    if (check_pool_running())
    {
        return;
    }
    thread_pool_mode_ = mode;
}
// 设置线程池的最大线程数量【cached模式下使用】
void ThreadPool::set_max_thread_num(int max_thread_num)
{
    if (check_pool_running())
    {
        return;
    }
    if (thread_pool_mode_ == ThreadPoolMode::CACHED)
    {
        max_thread_num_ = max_thread_num;
    }
}

// 设置线程池的最大空闲时间【cached模式下使用】
void ThreadPool::set_max_idle_time(int max_idle_time)
{
    if (check_pool_running())
    {
        return;
    }
    max_thread_idle_time_ = max_idle_time;
}

// 设置任务队列的最大上限阈值
void ThreadPool::set_task_queue_max_hold(int max_hold)
{
    if (check_pool_running())
    {
        return;
    }
    task_queue_max_threshold_ = max_hold;
}

// 提交任务到线程池
Result ThreadPool::submit_task(std::shared_ptr<Task> task)
{
    // 获取锁
    std::unique_lock<std::mutex> lock(task_queue_mutex_);
    // 线程通信， 等待任务队列有空余，把当前任务加入 任务队列
    /**
     *  等待任务队列有空余
     *   1) wait(lock,条件)                    一直等
     *   2）wait_for(lock,超时时长N,条件)        等待了N时长后，就不再等了 ;
     *          - 如果返回值是 false， 说明等待了N时长后，依然条件不满足
     *   3) wait_until(lock,超时截止时间N,条件)  截止第N时间，就不再等
     *
     */
    bool state_ = cond_task_not_full_.wait_for(lock, std::chrono::seconds(max_wait_time_), [&]() -> bool
                                               { return task_queue_.size() < task_queue_max_threshold_; }); // 等待任务队列未满， 即等待cond_task_not_full_条件变量 ; 进入等待状态后释放锁; 等待1S
    if (!state_)
    {
        // 等待超时， 任务队列依然未空， 提交任务失败
        // std::cout << "ThreadPool::submit_task(std::shared_ptr<Task> task) task_queue_ is full, submit task fail!" << std::endl;
        std::cout << "submit_task fail! \n";
        return Result(task, false);
    }

    // std::cout << "ThreadPool::submit_task(std::shared_ptr<Task> task)  submit task success! thread id :" << std::this_thread::get_id() << std::endl;
    std::cout << "submit_task success!  \n";
    // << std::this_thread::get_id() << "\n";
    // 任务队列未满， 即cond_task_not_full_条件变量满足， 将任务加入task_queue_
    task_queue_.emplace(task);
    task_cnt_++;

    // 因为新放入任务，则任务队列不为空，cond_task_not_empty_进行通知
    cond_task_not_empty_.notify_all();

    // 需要根据任务数量和空闲线程数量，判断是否需要创建新的线程出来 【cached模式， 任务处理比较紧急 ，场景小而快的任务】
    if (thread_pool_mode_ == ThreadPoolMode::CACHED &&
        task_cnt_ >= thread_idle_num_ &&
        thread_current_num_ < max_thread_num_)
    {
        // 创建新线程
        std::cout << "CACHED模式，触发创建新线程 \n";
        std::unique_ptr<Thread> ptr(new Thread(std::bind(&ThreadPool::thread_func, this, std::placeholders::_1))); // 创建线程对象，并绑定【方式一】
        int thread_id = ptr->get_thread_id();
        // 将线程对象加入线程池
        threads_.emplace(thread_id, std::move(ptr));
        // 启动线程
        threads_[thread_id]->start();

        // 修改线程个数相关的变量
        thread_current_num_++;
        thread_idle_num_++;
    }

    // 返回Result对象
    // 思路一：Result是属于某个任务的 task->getResult()  ----  XX ---此路不通，  由于线程执行完task之后，task对象就被析构掉了，此时已经无法进行 task->getResult()
    // 思路二：Result(task),  用户Result把task包装起来
    return Result(task, true);
}

// 线程池内部的 线程函数， 用于线程对象去执行 【通过std::bind 在 new Thread对象时】
void ThreadPool::thread_func(int thread_id)
{
    // std::cout << "begin thread_func():" << std::this_thread::get_id() << "\n ";
    // std::cout << "end thread_func():" << std::this_thread::get_id() << "\n ";

    auto last_time = std::chrono::high_resolution_clock::now();

    // 线程内部循环， 不断从任务队列中取出任务，并执行
    while (true) // 所有任务必须执行完成，线程池才能回收所有线程资源
    {
        // 从任务队列中取出任务
        std::shared_ptr<Task> task_;
        {
            // 取锁
            std::unique_lock<std::mutex> lock(task_queue_mutex_);

            // std::cout << "ThreadPool::thread_func() try to get task , thread id :" << std::this_thread::get_id() << std::endl;
            std::cout << "thread_func 尝试获取任务，线程id是:" << std::this_thread::get_id() << "\n";

            // cached模式下，有可能创建了很多线程； 但空闲时间超过了60s, 应把多余的线程结束回收掉（超过 初始数量的其他线程）
            // 当前时间 -  上一次线程执行的时间 >60S
            //  每秒返回一次，  需要区分：超时返回、任务执行返回
            while (task_queue_.empty())
            {
                // 线程池运行结束，回收资源
                if (!running_)
                {
                    threads_.erase(thread_id); // 将线程从线程池 移除
                    std::cout << "thread " << std::this_thread::get_id() << " exit\n";
                    cond_exit_.notify_all(); // 通知其他线程， 退出
                    return;
                }

                if (thread_pool_mode_ == ThreadPoolMode::CACHED)
                {
                    // 超时返回
                    if (std::cv_status::timeout == cond_task_not_empty_.wait_for(lock, std::chrono::seconds(1)))
                    {
                        auto now = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - last_time);
                        if (duration.count() >= max_thread_idle_time_ && thread_current_num_ > init_thread_num_)
                        {
                            // 执行超时任务
                            // 开始回收当前线程， 记录线程数量的相关变量值修改
                            // 把线程对象，从线程池的容器中删除

                            std::cout << "开始回收当前线程 \n";
                            //  << std::this_thread::get_id() << std::endl;
                            threads_.erase(thread_id);
                            thread_current_num_--;
                            thread_idle_num_--;
                            std::cout << "thread " << std::this_thread::get_id() << " exit\n";
                            return;
                        }
                    }
                }

                else
                {

                    // 等待任务队列不为空，即等待cond_task_not_empty_条件变量
                    cond_task_not_empty_.wait(lock, [&]() -> bool
                                              { return !task_queue_.empty(); }); // 进入等待状态后释放锁; 等待直到cond_task_not_empty_条件变量满足， 即等待任务队列
                }
            }

            thread_idle_num_--; // 空闲线程数量--

            // std::cout << "ThreadPool::thread_func() get task success , thread id :" << std::this_thread::get_id() << std::endl;
            std::cout << "thread_func 获取任务成功，线程id是:" << std::this_thread::get_id() << "\n";

            task_ = task_queue_.front(); // 任务队列不为空， 即cond_task_not_empty_条件变量满足， 将任务从任务队列中取出
            task_queue_.pop();           // 出队
            task_cnt_--;                 // task数量减减

            // 任务队列已空， 即cond_task_not_empty_条件变量不满足， 通知其他线程继续 提取任务
            if (!task_queue_.empty())
            {
                cond_task_not_empty_.notify_all();
            }

            // 取出任务之后需要cond_task_not_full_通知,可以继续提交任务
            cond_task_not_full_.notify_all();
        }

        // 执行任务 【应该在锁外执行】
        if (task_ != nullptr)
        {
            // std::cout << "ThreadPool::thread_func()  run task  , thread id :" << std::this_thread::get_id() << std::endl;
            std::cout << "thread_func run task \n";
            //  << std::this_thread::get_id() << "\n";
            task_->exec(); // 执行任务，把任务的返回值set_val 方法给到Result
        }

        thread_idle_num_++;                                    // 执行完后 空闲线程++
        last_time = std::chrono::high_resolution_clock::now(); // 线程执行完后， 最新的当前时间
    }
}

int Thread::generate_thread_id_ = 0;

// 线程构造
Thread::Thread(std::function<void(int)> func) : func_(func), thread_id_(generate_thread_id_++)
{
}

// 线程析构
Thread::~Thread()
{
}

// 线程启动
void Thread::start()
{
    // 创建一个线程，来执行一个线程函数
    std::thread t(func_, thread_id_); // c++11  线程对象t  和线程函数func_
    t.detach();                       // 线程分离
}

int Thread::get_thread_id() const
{
    return thread_id_;
}

void Task::set_result(Result *result)
{
    std::cout << "Task::set_result\n";
    result_ = result;
}

void Task::exec()
{ // 执行
    std::cout << "task exec\n";
    if (result_ != nullptr)
    {
        std::cout << "开始调用result_->set_val(run())\n";
        result_->set_val(run()); // 此处发生多态调用
    }
}