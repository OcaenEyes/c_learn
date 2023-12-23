/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-23 03:45:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-23 06:10:25
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/03-const-一二级指针的结合使用/const-一二级指针的结合.cpp
 * @Description: 注释信息
 */

#include <iostream>
#include <typeinfo>
/**
 * const 修饰的量 叫常量
 * 普通变量和常量的区别：1.编译方式不同， 2.不能作为左值
 *
 * const 修饰的常量常出现的错误：
 * 1.常量不能作为左值 【即：直接修改常量的值会报错】
 * 2.不能把常量的地址 泄露给一个普通的指针 或 普通的引用变量 【即：间接修改常量的值会报错】
 *
 *
 *
 * const 和一级指针的结合
 * c++ 的语言规范：const修饰的是离它最近的类型
 *
 * const int*p;  //const 【指针p的指向是常量】  可以指向任意int类型的内存； 但不能通过指针间接修改指向的内存的值
 * int const *p; //const 【指针p的指向是常量】 可以指向任意int类型的内存； 但不能通过指针间接修改指向的内存的值
 *
 * int *const p; //const 【指针p是常量】 不能再指向其他内存， 但可以通过指针解引用 修改指向的内存的值
 *
 * const int *const p; //第一个const 最近的类型是int*，【指针p本身是常量】不能再指向其他内存； 第二个const修饰p本身,也不能通过解引用修改值
 *
 * ==========================
 *
 * int* << const int*  错误
 * const int* << int*  可以
 *
 *
 *
 * int** << const int**  错误
 * const int** << int**  错误
 *
 * int** << int* const*  错误  【int* const* 属于const与一级指针的结合】
 * int* const* << int**  错误
 */

// const与一级指针
void const_ptr()
{
}

// const与二级指针
/**
 * const int **q; // const最近的类型是int， 修饰的表达式是**q,**q不能被赋值
 * int* const *q; // const最近的类型是int*， 修饰的表达式是*q,*q不能被赋值
 * int** const q; // const最近的类型是int**， 修饰的表达式是q,q不能被赋值
 */
void const_ptr_ptr()
{
    int a = 10;
    int *p = &a;
    // const int **q = &p; // 错误的转换  error: invalid conversion from 'int**' to 'const int**' [-fpermissive]
}

int main()
{
    const int a = 10; // 常量

    const_ptr_ptr();

    return 0; // success
}