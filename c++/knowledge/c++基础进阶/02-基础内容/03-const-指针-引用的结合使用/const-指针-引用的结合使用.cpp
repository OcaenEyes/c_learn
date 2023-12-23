/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-22 07:25:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-22 15:09:43
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/03-const-指针-引用的结合使用/const-指针-引用的结合使用.cpp
 * @Description: 注释信息
 */
#include <iostream>

/**
 * 1. 引用与指针的区别 【引用是一种更安全的指针】
 * 引用必须初始化， 引用只有一级引用
 * 指针可以不初始化， 指针可以有多级指针
 * 2. 定义一个引用变量 和定义一个指针变量，其汇编语言是一摸一样的
 */

/**
 * @brief 交换变量的值,直接用int形参传值的方式 无法成功
 *
 * @param a
 * @param b
 */
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

/**
 * @brief 交换变量的值,用int类型指针形参传值，可以成功
 *
 * @param x
 * @param y
 */
void swap_ptr(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * @brief 交换变量的值,用int类型引用形参传值，可以成功
 *
 * @param x
 * @param y
 */
void swap_ref(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int main()
{
    int a = 10;
    int *p = &a; // p指针指向a的地址
    int &b = a;  // b引用a的内存； 引用必须初始化

    *p = 20; // 使用指针p修改a对应的内存的值
    // 20 20 20
    std::cout << "使用指针p修改a对应的内存的值" << a << " " << *p << " " << b << "\n";

    b = 30; // 使用引用b修改a对应内存的值 【b相当于a对应内存的别名】
    // 30 30 30
    std::cout << "使用引用b修改a对应内存的值" << a << " " << *p << " " << b << "\n";

    swap(a, b); // 无法改变a，b的值

    swap_ptr(&a, &b); // 可以交换a，b的值

    swap_ref(a, b); // 可以交换a，b的值

    int array[5] = {};
    int *pp = array; // 指针指向数组
    std::cout << "sizeof(array) :" << sizeof(array) << "\n";
    std::cout << "sizeof(pp)" << sizeof(pp) << "\n";

    int(&qq)[5] = array; // 定义一个引用变量，来引用array数组
    std::cout << "sizeof(q)" << sizeof(qq) << "\n";

    return 0;
}