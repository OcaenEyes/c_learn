/*
两种类型的多任务处理：基于进程和基于线程。

基于进程的多任务处理是程序的并发执行。
基于线程的多任务处理是同一程序的片段的并发执行。
*/

// 创建线程
/*
#include <pthread.h>
pthread_create (thread, attr, start_routine, arg) 
在这里，pthread_create 创建一个新的线程，并让它可执行。下面是关于参数的说明：

参数	         描述
thread	        指向线程标识符指针。
attr	        一个不透明的属性对象，可以被用来设置线程属性。您可以指定线程属性对象，也可以使用默认值 NULL。
start_routine	线程运行函数起始地址，一旦线程被创建就会执行。
arg	            运行函数的参数。它必须通过把引用作为指针强制转换为 void 类型进行传递。如果没有传递参数，则使用 NULL。
创建线程成功时，函数返回 0，若返回值不为 0 则说明创建线程失败。
*/

// 终止线程
/*
#include <pthread.h>
pthread_exit (status) 
在这里，pthread_exit 用于显式地退出一个线程。
通常情况下，pthread_exit() 函数是在线程完成工作后无需继续存在时被调用。

如果 main() 是在它所创建的线程之前结束，并通过 pthread_exit() 退出，那么其他线程将继续执行。
否则，它们将在 main() 结束时自动被终止。
*/

#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

// 线程的运行函数
void *say_hello(void *args){
    cout << "Hello GZY" << endl;
    return 0;
}

int main(){
    // 定义线程的ID变量， 多个变量使用数组
    pthread_t tids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        /* code */
        // 参数依次是：创建线程ID， 线程参数， 调用的函数， 传入的函数参数
        int ret = pthread_create( &tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
            /* code */
            cout << "pthread_create error : error_code=" << ret << endl;
        }
    }
    // 等各个线程退出后，进程才结束
    pthread_exit(NULL);
    
}