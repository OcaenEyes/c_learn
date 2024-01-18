

/**
 * lock_guard<std::mutext> lock(mutex_); //  类似scoped_ptr , 栈上的局部对象，出作用域就会被释放
 *
 *
 *
 *
 * unique_lock<std::mutext> lock(mutex_);  // unique_ptr
 *
 */

#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cond;

int main()
{
    // mtx.lock();
    // mtx.unlock();

    // std::lock_guard出作用域即释放;  不能用在函数参数传递 或者 返回过程中；  只能在简单的临界区代码段的互斥操作中
    // std::lock_guard<std::mutex> guard(mtx);

    //  std::unique_lock， 可以用简单的临界区代码段的互斥操作中，也可以使用在函数调用的参数传递；
    std::unique_lock<std::mutex> lck(mtx);
    //  使线程进入等待状态；  且会调用lck.unlock(); 释放mtx互斥锁
    cond.wait(lck);

    return 0;
}