/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-23 13:28:45
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-23 14:40:56
 * @FilePath: /c++/knowledge/c++基础进阶/04-模板编程/01-函数模板.cpp
 * @Description: 注释信息
 */
#include <iostream>
#include <string.h>

/**
 * C++ 函数模板
 * 模板的意义： 对类型也可以进行参数化了
 *
 * 函数模板：前面一行有template <typename T, typename E,...> 定义模板参数列表
 * 模板的实例化：在函数调用点
 * 模板函数：才会被编译器所编译
 *
 *
 * 模板类型参数
 * 模板非类型参数
 *
 *
 * 模板的实参推演==>可根据用户 传入的实参类型，来推导出模板类型参数的具体类型
 * 模板的特例化（专用化）
 * 函数模板、模板的特例化、非模板函数的重载关系
 *
 * ！！！模板代码是不能在一个文件中定义，在另一个文件只能够使用的
 * ！！！！ 模板代码调用之前，一定要看到模板定义的地方，这样模板才能正常的实例化成能被编译器编译的代码
 *         因此模板代码都是放在头文件中
 */

// template <typename T, typename E,...> 定义模板参数列表

template <typename T>  // 定义模板参数列表
bool compare(T a, T b) // compare是一个函数模板
{
    std::cout << "template typename compare \n";
    return a > b;
}

// 告诉编译器，需要进行指定类型的模板实例化
template bool compare<int>(int, int);
template bool compare<double>(double, double);

// 针对compare函数模版，提供const char*类型的特例化版本
template <>
bool compare<const char *>(const char *a, const char *b)
{
    std::cout << "compare<const char*> \n";
    return strcmp(a, b) > 0;
}

// 非模板函数--普通函数
bool compare(const char *a, const char *b)
{
    std::cout << "compare(const char *a, const char *b) \n";
    return strcmp(a, b) > 0;
}

template <typename T, int SIZE> // 模板非类型参数，必须是整数类型（整数或地址、引用都可以）； 都是常量只能使用，不能修改
void sort(T *arr)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    // 函数的调用点， 编译器用用户指定的类型， 从原模板实例化一份函数代码出来-->即为生成了模板函数
    // bool compare<int> (int a, int b){
    //    return a>b;
    // }
    compare<int>(10, 20);

    // 函数的调用点
    compare<double>(10.1, 20.2);

    // 函数的调用点，函数模板实参的推演：会进行模板类型参数的具体类型
    compare(30, 20);

    compare("abv", "abc"); // 此时会默认优先调用 普通函数

    compare<const char *>("abv", "abc"); // 此时使用特例化版本

    int arr[] = {12, 5, 7, 89, 32, 21, 36};
    const int size = sizeof(arr) / sizeof(arr[0]);
    sort<int, size>(arr);

    for (auto &&i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
