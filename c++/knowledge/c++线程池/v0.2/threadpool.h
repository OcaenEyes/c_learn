/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-03 14:26:31
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-04 12:09:05
 * @FilePath: /c++/knowledge/c++线程池/v0.2/threadpool.h
 * @Description: 注释信息
 */
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <memory>
#include <unordered_map>

const int TASK_MAX_THRESHHOLD = 2; // INT32_MAX;
const int THREAD_MAX_THRESHHOLD = 10;
const int THREAD_MAX_IDLE_TIME = 10;

enum class ThreadPoolMode
{
    MODE_FIXED,
    MODE_CACHED,
};

class Thread
{

public:
    // 线程函数类型
    using ThreadFunc = std::function<void(int)>;

    Thread(ThreadFunc func);
    ~Thread();

    // 启动线程
    void start();
    // 获取线程ID
    int get_thread_id() const;

private:
    ThreadFunc func_;
    // 静态变量-线程ID，用于生成线程ID
    static int generate_id_;
    // 线程ID
    int thread_id_;
};

Thread::Thread(ThreadFunc func) : func_(func), thread_id_(generate_id_++)
{
    std::cout << "Thread ID: " << thread_id_ << "init\n";
}

Thread::~Thread()
{
}

// 启动线程
void Thread::start()
{
    // 创建线程
    std::thread t(func_, thread_id_);
    // 分离线程
    t.detach();
}

// 获取线程ID
int Thread::get_thread_id() const
{
    return thread_id_;
}

// 静态变量-线程ID，用于生成线程ID
int Thread::generate_id_ = 0;

class ThreadPool
{

public:
    ThreadPool();
    ~ThreadPool();
    // 设置线程池模式
    void set_mode(ThreadPoolMode mode);
    // 设置任务队列阈值
    void set_task_queue_threshold(int threshold);
    // 设置线程池阈值
    void set_thread_num_threshold(int threshold);
    // 设置线程空闲时间
    void set_thread_idle_time(int idle_time);
    // 启动线程池
    void start(int num = std::thread::hardware_concurrency());

    // 提交任务
    template <typename F, typename... Args>
    auto submit_task(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;

    ThreadPool(const ThreadPool &) = delete;            // 禁用复制构造函数
    ThreadPool &operator=(const ThreadPool &) = delete; // 禁用赋值操作

private:
    void thread_func(int thread_id);
    bool check_runing_state() const;

private:
    // 线程池模式
    ThreadPoolMode mode_;
    // 线程池运行状态
    std::atomic<bool> running_;
    // 线程池容器
    std::unordered_map<int, std::unique_ptr<Thread>> threads_;
    // 任务队列
    std::queue<std::function<void()>> task_queue_;
    // 任务队列锁
    std::mutex task_queue_mutex_;

    // 线程退出
    std::condition_variable cond_exit_;
    // 任务队列非空
    std::condition_variable cond_not_empty_;
    // 任务队列不满
    std::condition_variable cond_not_full_;

    // 任务队列阈值
    int thread_num_threshold_;
    // 任务队列阈值
    int task_queue_threshold_;
    // 空闲线程的最大空闲时间
    int thread_idle_time_;
    // 初始线程数
    int init_thread_num_;

    // 用于记录当前线程池中的线程数
    std::atomic_int cur_thread_num_;
    // 用于记录当前任务队列中的任务数
    std::atomic_int task_queue_size_;
    // 用于记录当前空闲的线程数
    std::atomic_int thread_idle_count_;
};

ThreadPool::ThreadPool() : running_(false),
                           mode_(ThreadPoolMode::MODE_FIXED),

                           thread_idle_time_(THREAD_MAX_IDLE_TIME),      // 默认空闲时间为THREAD_MAX_IDLE_TIME
                           init_thread_num_(0),                          // 默认初始线程数为0
                           cur_thread_num_(0),                           // 初始化当前总线程数为0
                           thread_idle_count_(0),                        // 初始化当前空闲线程数为0
                           thread_num_threshold_(THREAD_MAX_THRESHHOLD), // 初始化线程池阈值为THREAD_MAX_THRESHHOLD

                           task_queue_size_(0),                       // 初始化任务队列大小为0
                           task_queue_threshold_(TASK_MAX_THRESHHOLD) // 初始化任务队列阈值为TASK_MAX_THRESHHOLD
{
}

ThreadPool::~ThreadPool()
{
    running_ = false; // 设置线程池状态为非运行状态

    std::unique_lock<std::mutex> lock(task_queue_mutex_); // 取锁
    cond_not_empty_.notify_all();                         // 通知所有等待的线程
    cond_exit_.wait(lock, [this]
                    { return cur_thread_num_ == 0; }); // 等待所有线程执行完毕
}

void ThreadPool::set_mode(ThreadPoolMode mode)
{
    if (check_runing_state())
    {
        return;
    }
    mode_ = mode; // 设置线程池模式
}

void ThreadPool::set_task_queue_threshold(int threshold)
{
    if (check_runing_state())
    {
        return;
    }
    task_queue_threshold_ = threshold; // 设置任务队列阈值
}

void ThreadPool::set_thread_num_threshold(int threshold)
{
    if (check_runing_state())
    {
        return;
    }
    if (mode_ == ThreadPoolMode::MODE_CACHED)
    {
        thread_num_threshold_ = threshold; // 设置线程池阈值
    }
}

void ThreadPool::set_thread_idle_time(int idle_time)
{
    if (check_runing_state())
    {
        return;
    }
    if (mode_ == ThreadPoolMode::MODE_CACHED)
    {
        thread_idle_time_ = idle_time; // 设置线程空闲时间
    }
}

bool ThreadPool::check_runing_state() const
{
    return running_; // 检查线程池是否处于运行状态
}

void ThreadPool::thread_func(int thread_id)
{
    std::cout << "Thread " << thread_id << " start thread_func." << std::endl;
    auto lasttime = std::chrono::high_resolution_clock::now(); // 获取当前时间
    while (true)
    {
        std::function<void()> task; // 定义任务函数
        {
            std::unique_lock<std::mutex> lock(task_queue_mutex_); // 取锁
            while (task_queue_.empty())
            {
                std::cout << "任务为空,持续循环中。。。\n";
                if (!check_runing_state())
                {
                    std::cout << "线程池关闭且任务为空\n";
                    threads_.erase(thread_id); // 删除线程
                    cond_exit_.notify_all();   // 通知所有等待线程
                    return;
                }

                if (mode_ == ThreadPoolMode::MODE_CACHED)
                {
                    if (cur_thread_num_ > init_thread_num_ &&
                        std::cv_status::timeout == cond_not_empty_.wait_for(lock, std::chrono::seconds(1)))
                    {
                        std::cout << "任务为空且是动态增加线程模式， 当前线程数量大于初始数量， 且等到任务超时了。。\n";
                        auto now = std::chrono::high_resolution_clock::now();                             // 获取当前时间
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lasttime); // 计算时间
                        if (duration.count() >= thread_idle_time_)
                        {
                            threads_.erase(thread_id); // 删除线程
                            cur_thread_num_--;         // 减少线程数
                            thread_idle_count_--;      // 减少空闲线程数
                            return;                    // 退出线程
                        }
                    }
                }
                else
                {
                    std::cout << "等待任务不为空\n";
                    cond_not_empty_.wait(lock, [this]
                                         { return !task_queue_.empty(); });
                    std::cout << "等待任务结束\n";
                }
            }
            std::cout << "线程 " << thread_id << " 拿到任务\n";
            thread_idle_count_--;       // 减少空闲线程数
            task = task_queue_.front(); // 获取任务
            task_queue_.pop();          // 删除任务
            task_queue_size_--;         // 减少任务数

            if (!task_queue_.empty())
            {
                std::cout << "通知等待任务不为空的线程\n";
                cond_not_empty_.notify_all(); // 通知其他等待线程
            }
            std::cout << "通知等待任务不为满的线程\n";
            cond_not_full_.notify_all(); // 通知其他等待线程
        }
        if (task != nullptr)
        {
            std::cout << "线程 " << thread_id << " 开始执行任务\n";
            task(); // 执行任务
            std::cout << "线程 " << thread_id << " 执行任务结束\n";
        }

        thread_idle_count_++;                                 // 增加空闲线程数
        lasttime = std::chrono::high_resolution_clock::now(); // 更新上次空闲时间
    }
}

void ThreadPool::start(int num)
{
    running_ = true;        // 设置线程池为运行状态
    init_thread_num_ = num; // 设置初始线程数
    cur_thread_num_ = num;  // 设置当前线程数

    for (int i = 0; i < num; i++)
    {
        std::unique_ptr<Thread> thread(new Thread(std::bind(&ThreadPool::thread_func, this, std::placeholders::_1))); // 创建线程
        int thread_id = thread->get_thread_id();                                                                      // 获取线程ID
        threads_.emplace(thread_id, std::move(thread));                                                               // 将线程加入线程池
    }

    for (auto &&i : threads_)
    {
        i.second->start(); // 启动线程
        thread_idle_count_++;
        std::cout << "Thread " << i.first << " started" << std::endl;
    }
}

template <typename F, typename... Args>
auto ThreadPool::submit_task(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    std::cout << "submit task\n";
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...)); // 创建任务

    std::future<return_type> res = task->get_future(); // 获取任务结果

    std::unique_lock<std::mutex> lock(task_queue_mutex_); // 获取锁
    if (!cond_not_full_.wait_for(lock, std::chrono::seconds(1), [this]
                                { return task_queue_.size() < task_queue_threshold_; }))
    {
        /* code */
    }


    task_queue_.emplace([task]() { (*task)(); }); // 将任务加入队列
    task_queue_size_++;

    cond_not_empty_.notify_all(); // 通知有新的任务

    return res;
}
