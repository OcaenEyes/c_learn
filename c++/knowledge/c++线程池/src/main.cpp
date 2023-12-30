/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-28 09:49:21
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-29 14:15:48
 * @FilePath: /c++/knowledge/c++线程池/src/main.cpp
 * @Description: 注释信息
 */

#include "../include/threadpool.h"
#include <iostream>

/**
 * 每个task进行一组计算
 * main thread :给每一个线程分配计算区间，并等待他们返回结果， main thread进行最终的结果合并
 */

class MyTask : public Task
{
public:
    MyTask(int begin, int end) : begin_(begin), end_(end)
    {
    }
    // 问题一：怎么设计run函数的返回值，可以表示任意类型
    // 通过Any上帝类 ; c++17才具有的类型,  通过c++11实现
    // Any类型： 可以接受任意的其他类型 template
    //      怎么样能让一个类型，可以 指向 其他任意类型呢？
    //         通过指针实现， 基类类型---> 指向 派生类类型
    Any run() override
    {
        // 执行任务
        std::cout << "Task executed in thread :" << std::this_thread::get_id() << std::endl;
        // 模拟任务执行时间
        // std::this_thread::sleep_for(std::chrono::seconds(2));

        int sum = 0;
        for (int i = 0; i < end_; i++)
        {
            sum += i;
        }

        std::cout << "Task finished in thread :" << std::this_thread::get_id() << std::endl;
        return sum;
    }

private:
    int begin_;
    int end_;
};

int main()
{
    ThreadPool pool; // 创建一个的线程池
    pool.start(5);   // 启动5个工作线程

    // 提交任务到线程池
    // 问题二：如何设计Result机制 来接收提交任务之后的线程处理结果呢？
    // 需要先有submit提交，执行之后有结果res，才能有结果res.get, 需要用到线程通信，使用信号量实现

    Result res = pool.submit_task(std::make_shared<MyTask>());
    int sum = res.get().cast_<int>(); // 读取到task在线程调度运行之后的结果

    pool.submit_task(std::make_shared<MyTask>());
    pool.submit_task(std::make_shared<MyTask>());
    pool.submit_task(std::make_shared<MyTask>());
    pool.submit_task(std::make_shared<MyTask>());

    getchar();
    return 0;
}