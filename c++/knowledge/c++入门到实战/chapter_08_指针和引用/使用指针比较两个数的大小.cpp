/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 11:01:26
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 12:13:22
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/使用指针比较两个数的大小.cpp
 * @Description: 注释信息
 */
#include <iostream>

int main(int argc, char *argv[])
{
    int *p1;
    int *p2;

    int *p;

    int a, b;

    std::cout << "输入a:" << std::endl;
    std::cin >> a;

    std::cout << "输入b:" << std::endl;
    std::cin >> b;

    p1 = &a;
    p2 = &b;

    if (a < b)
    {
        p = p1;
        p1 = p2;
        p2 = p;
    }

    std::cout << "a=" << a << " "
              << "b=" << b << std::endl;

    std::cout << "max地址=" << p1 << " "
              << "min地址=" << p2 << std::endl;
              
    std::cout << "max=" << *p1 << " "
              << "min=" << *p2 << std::endl;
    return 0;
}

// 指针运算
/**
 * 指针变量， 存储的是地址值； 对指针做运算就等于对地址做运算
 * 
 */                                                  