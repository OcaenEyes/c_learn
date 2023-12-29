#include "../include/threadpool.h"
#include <iostream>

class MyTask : public Task
{
public:
    MyTask() {}
    ~MyTask() {}
    void run()
    {
        // 执行任务
        std::cout << "Task executed in thread :" << std::this_thread::get_id() << std::endl;
        // 模拟任务执行时间
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Task finished in thread :" << std::this_thread::get_id() << std::endl;
    }

private:
};

int main()
{
    ThreadPool pool; // 创建一个的线程池
    pool.start(5);   // 启动5个工作线程
    // 提交任务到线程池
    pool.submit_task(std::make_shared<MyTask>());
}