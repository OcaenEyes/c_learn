/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-02 09:16:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-04 16:54:04
 * @FilePath: /c++/knowledge/c++线程池/v0.2/main.cpp
 * @Description: 注释信息
 */

#include "threadpool.h"

/**
 * 1.如何能让线程池提交任务更加方便
 *      std::thread t1(sum1, 1, 2);
 *      std::thread t2(sum2, 1, 2, 3);
 *   1）解决思路：submit_task ，可变参数模板编程
 *
 * 2.处理返回值的Result、Any等相关类型，怎么进行代码精简？
 *      c++11 线程库 thread    packaged_task(function函数对象)   async
 *      使用future来代替Result节省线程池代码
 *
 */

int sum1(int a, int b)
{
    return a + b;
}

int sum2(int a, int b, int c)
{
    return a + b + c;
}
int forsum(int a)
{
    int sum = 0;
    for (int i = 0; i < a; i++)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    // std::thread t1(sum1, 1, 2);
    // std::thread t2(sum2, 1, 2, 3);
    // t1.join();
    // t2.join();

    // 包装一下任务
    // std::packaged_task<int(int, int)> task(sum1);
    // // future <===> Result
    // std::future<int> result = task.get_future();
    // // 使用包装的任务 调用执行
    // task(4, 2);
    // // 获取结果 [会等到task里面的sum函数执行结束]
    // std::cout << "task(4, 2)----result = " << result.get() << std::endl;

    // // 将task放入一个独立的线程
    // std::thread t1(std::move(task), 10, 20);
    // t1.detach(); // 分离线程

    ThreadPool pool;
    pool.start(4);

    auto r1 = pool.submit_task(forsum, 10000);
    std::cout << "r1.get() = " << r1.get() << "\n";

    auto r2 = pool.submit_task(sum2, 1, 2, 3);
    std::cout << "r2.get() = " << r2.get() << "\n";

    auto r3 = pool.submit_task([](int answer)
                               { return answer; },
                               42);
    std::cout << "r3.get() = " << r3.get() << "\n";

    auto r4 = pool.submit_task([](int a, int b)
                               { return a + b; },
                               1, 2);
    std::cout << "r4.get() = " << r4.get() << "\n";
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);
    pool.submit_task([](int a, int b)
                     { return a + b; },
                     1, 2);

    return 0;
}