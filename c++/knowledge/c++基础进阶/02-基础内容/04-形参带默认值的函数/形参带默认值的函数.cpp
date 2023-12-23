/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-22 06:45:24
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-22 06:51:23
 * @FilePath: /c++/knowledge/c++基础进阶/02-基础内容/04-形参带默认值的函数/形参带默认值的函数.cpp
 * @Description: 注释信息
 */

#include <iostream>

/**
 * @brief 
 * 1. 形参默认值需要从右往左给
 * 2. 调用效率
 * 3. 定义处可以给形参默认值； 声明处也可以给形参默认值； 但形参默认值 只能出现一次
 *
 * @param a
 * @param b 设置默认值10
 * @return int
 */
int sum(int a, int b = 10)
{
    return a + b;
}

int main()
{
    int a = 10;
    int b = 20;
    int ret = sum(a, b);

    std::cout << "ret:" << ret << "\n";

    return 0;
}