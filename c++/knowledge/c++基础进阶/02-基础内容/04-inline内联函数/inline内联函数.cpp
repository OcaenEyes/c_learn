/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-22 06:52:31
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-22 07:02:11
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/04-inline内联函数/inline内联函数.cpp
 * @Description: 注释信息
 */
#include <iostream>

/// @brief
/// inline内联函数，在编译过程中，就没有函数的调用了， 把函数的代码进行展开处理了
/// inline内联函数，不再生成相应的函数符号
/// inline只是建议 编译器把这个函数处理成内敛函数
/// 但不是所有的inline都会被编译器处理成内联函数， 譬如递归
/// debug版本上，inline是不起作用的； 在release版本才会出现
///
/// @param x
/// @param y
/// @return
inline int inline_sum(int x, int y)
{
    return x + y;
}

int sum(int x, int y)
{
    return x + y;
}

int main()
{
    int a = 10;
    int b = 20;

    int ret1 = inline_sum(a, b);

    int ret2 = sum(a, b); // 此处有标准的函数调用过程， 参数压栈， 函数栈帧的开辟和回退过程 【有函数调用的开销】

    return 0;
}