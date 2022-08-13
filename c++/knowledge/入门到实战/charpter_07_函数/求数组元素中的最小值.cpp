/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 00:54:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 01:03:33
 * @FilePath: /c++/knowledge/入门到实战/charpter_07_函数/求数组元素中的最小值.cpp
 * @Description: 注释信息
 */

/**
 * @brief
 *
 * @param ary 整数数组
 * @param n
 * @return int  最小值
 */

#include <iostream>

int min(int ary[20], int n)
{
    int m, i;
    m = ary[0];
    for (i = 1; i < n; i++)
    {
        if (ary[i] < m)
        {
            m = ary[i];
        }
    }
    return m;
}

int main()
{
    int a[20], m, n, i;
    printf("请输入元素个数：\n");
    scanf("%d", &n);
    printf("请输入元素:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    m = min(a, n);
    printf("最小值是：%3d\n", m);

    return 0;
}