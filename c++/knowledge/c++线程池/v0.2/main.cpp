

#include <thread>
#include <functional>
#include <iostream>

/**
 * 1.如何能让线程池提交任务更加方便
 *      std::thread t1(sum1, 1, 2);
 *      std::thread t2(sum2, 1, 2, 3);
 *   1）解决思路：submit_task ，可变参数模板编程
 * 
 * 2.处理返回值的Result、Any等相关类型，怎么进行代码精简？
 *      c++11 线程库 thread    packaged_task(function函数对象)   async
 *      
 */

int sum1(int a, int b) {
    return a + b;
}

int sum2(int a, int b,int c) {
    return a + b + c;
}

int main(){
    std::thread t1(sum1, 1, 2);
    std::thread t2(sum2, 1, 2, 3);

}