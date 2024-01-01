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
    // 创建一个的线程池
    ThreadPool pool;
    // 设置线程池的工作模式
    pool.set_mode(ThreadPoolMode::CACHED); // 在线程池start之前可以设置

    // 启动5个工作线程
    pool.start(1);

    // 提交任务到线程池
    // 问题二：如何设计Result机制 来接收提交任务之后的线程处理结果呢？
    // 需要先有submit提交，执行之后有结果res，才能有结果res.get, 需要用到线程通信，使用信号量实现

    Result res1 = pool.submit_task(std::make_shared<MyTask>(1, 10));
    int sum1 = res1.get().cast_<int>(); // 读取到task在线程调度运行之后的结果

    Result res2 = pool.submit_task(std::make_shared<MyTask>(11, 20));
    int sum2 = res2.get().cast_<int>(); // 读取到task在线程调度运行之后的结果

    Result res3 = pool.submit_task(std::make_shared<MyTask>(21, 30));
    int sum3 = res3.get().cast_<int>(); // 读取到task在线程调度运行之后的结果

    Result res4 = pool.submit_task(std::make_shared<MyTask>(31, 40));
    int sum4 = res4.get().cast_<int>(); // 读取到task在线程调度运行之后的结果

    int sum = sum1 + sum2 + sum3 + sum4;
    std::cout << "sum = " << sum << std::endl;

    /**
     * Master - Slave线程模型
     * 1.Master线程用来分解任务，然后给各个Slave线程分配任务
     * 2.等待各个Slave线程执行完成任务，返回结果
     * 3.Master线程合并各个任务结果，输出
     */

    getchar();
    return 0;
}