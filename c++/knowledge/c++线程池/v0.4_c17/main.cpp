/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-03 12:10:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-03 13:34:30
 * @FilePath: /c++/knowledge/c++线程池/v0.4_c17/main.cpp
 * @Description: 注释信息
 */
#include "threadpool.h"
#include <iostream>


// 编译命令 ：g++ -std=c++17 main.cpp -pthread -o main
int main()
{
    // create thread pool with 4 worker threads
    ThreadPool pool(4);

    // enqueue and store future
    auto result = pool.enqueue([](int answer)
                               { return answer; },
                               42);

    // get result from future
    std::cout << result.get() << std::endl;
}