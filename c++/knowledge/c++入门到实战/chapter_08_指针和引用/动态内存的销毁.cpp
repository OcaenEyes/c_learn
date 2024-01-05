/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 06:22:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 06:42:13
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/动态内存的销毁.cpp
 * @Description: 注释信息
 */
#include <iostream>
using namespace std;

int *newPointerGet(int *p1)
{
    int k1 = 55;
    p1 = new int; // 变为堆内存
    *p1 = k1;     // int型 变量赋值操作
    return p1;
}

int *pointerGet(int *p2)
{
    int k2 = 55;
    p2 = &k2; // 指向函数中定义变量 所在的栈内存，  此段内存在 函数执行后销毁
    cout << "p2此时指向的值：" << *p2 << endl;
    return p2;
}
int main(int argc, char *argv[])
{
    cout << "输出函数各自返回指针 所指向的内存的值" << endl;
    int *p = NULL;
    p = newPointerGet(p); // p具有堆内存地址

    int *i = NULL;
    i = pointerGet(i); // i具有栈内存地址，内存内容被销毁

    cout << "new Get:" << *p << "; get " << *i << endl;

    cout << "i所指向的内存没有立刻销毁， 执行一个输出语句后：" << endl;

    cout << "new Get:" << *p << "; get " << *i << endl;

    delete p;
    cout << "销毁堆内存后：" << endl;
    cout << "new Get:" << *p << "; get " << *i << endl;
    return 0;
}
