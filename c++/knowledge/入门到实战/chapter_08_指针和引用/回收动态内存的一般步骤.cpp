/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 07:00:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 07:34:22
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/回收动态内存的一般步骤.cpp
 * @Description: 注释信息
 */

/**
 * @file 回收动态内存的一般步骤.cpp
 * @author ocean gzy (you@domain.com)
 * @brief 
 * 当没有指针指向一块未被回收的堆内存时，此块内存犹如丢失一样，就叫做 内存泄露。
 * 
 * @version 0.1
 * @date 2022-08-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[])
{
    int *p = new int;
    *p = 3;

    int k = 5;

    swap(p, &k);
    cout << "*p 对应的值" << *p<< endl;
    cout << "k:" << k << endl;

    delete p; // 回收动态内存
    p= NULL; // 将p置空， 防止使用已销毁的内存。  与delete语句不可颠倒，不然会导致内存泄露
}
