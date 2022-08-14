/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 06:11:29
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 06:20:48
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/动态分配内存空间.cpp
 * @Description: 注释信息
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int *p1 = NULL;
    p1 = new int; // 申请动态分配，new是C++中申请动态内存的关键字

    *p1 = 111; // 动态分配的内存 存储的内容变为111的 整型变量

    cout << "p1内 存储的内容：" << *p1 << "p1所指向的地址：" << p1 << endl;
    int *p2;
    int k; //栈中的变量
    // *p2 = 222;  ** 直接复制会导致错误 **
    p2 = &k;   // 分配栈内存
    *p2 = 222; // 分配栈内存后可赋值
    cout << "p2内 存的内容：" << *p2 << "p2指向的地址：" << p2 << endl;

    return 0;
}
