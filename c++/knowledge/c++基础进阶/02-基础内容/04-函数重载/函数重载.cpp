/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-22 15:36:04
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-22 15:53:37
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/04-函数重载/函数重载.cpp
 * @Description: 注释信息
 */
#include <iostream>
#include <string.h>

/**
 * 什么是函数重载？
 * ：一组函数，其中函数名相同，参数列表的个数或者类型不同，就称作函数重载
 * ：一组函数要称得上重载，需要是在同一个作用域中
 * ： const或者volatile的时候
 *
 *
 * 1.C++为什么支持重载？c不支持
 * ： c++代码产生函数符号的时候，函数名+参数列表类型组成
 *    c代码产生函数符号的时候， 函数名来决定
 *
 * 2.函数重载需要注意什么？
 *
 * 3.C++ 和C语言代码之间如何互相调用？
 *
 */

bool compare(int a, int b)
{
    std::cout << "compare_int_int "
              << "\n";
    return a > b;
}

bool compare(double a, double b)
{
    std::cout << "compare_double_double "
              << "\n";
    return a > b;
}

bool compare(const char *a, const char *b)
{
    std::cout << "compare_char*_char* "
              << "\n";
    return strcmp(a, b);
}

void func(int a)
{
}

void func(const int as)
{
}

int main()
{
    compare(10, 20);
    compare(10.0, 20.0);
    compare("aaaa", "bbbb");

    return 0;
}