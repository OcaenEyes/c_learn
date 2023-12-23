/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-22 02:55:15
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-22 06:39:25
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/深入理解new和delete/深入理解new和delete.cpp
 * @Description: 注释信息
 *
 */

#include <stdlib.h>

/**
 *
 * malloc和free，称作C的库函数
 *  void* malloc (size_t size);这个函数向内存申请一块连续可用的空间，并返回指向这块空间的指针。【仅用于开辟内存】
 *      如果开辟成功，则返回一个指向开辟好空间的指针。
 *      如果开辟失败，则返回一个NULL指针，因此malloc的返回值一定要做检查。
 *      返回值的类型是void*，所以malloc函数并不知道开辟空间的类型，具体在使用的时候使用者自己来决定。
 *      如果size为0，malloc的行为是标准未定义的，取决于编译器。
 *
 * new和delete，称作运算符
 *
 *
 * 1）new和malloc的区别是什么
 * new: 可以做内存开辟， 还可以做内存初始化操作， 开辟失败则抛出bad_alloc类型的异常
 * malloc: 仅开辟内存，开辟失败则返回nullptr
 *
 *
 * 2）delete和free的区别是什么
 *
 *
 */

int main()
{
    // malloc
    int *p = (int *)malloc(sizeof(int));
    if (p == nullptr)
    {
        return -1;
    }
    *p = 20;
    // free
    free(p);

    // new
    int *p1 = new int(20);
    // delete
    delete p1;

    // malloc 数组
    int *p2 = (int *)malloc(sizeof(int) * 20);
    if (p2 == nullptr)
    {
        return -1;
    }
    // free
    free(p2);

    // new
    int *p3 = new int[20];   // 不做初始化
    int *p4 = new int[20](); // 初始化为0
    // delete
    delete p3;
    delete p4;

    delete[] p3;
    delete[] p4;

    return 0;
}