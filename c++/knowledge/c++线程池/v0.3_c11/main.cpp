#include "threadpool.h"


// 编译命令 ：g++ main.cpp -pthread -o main
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