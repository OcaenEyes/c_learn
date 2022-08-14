/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 00:33:30
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 00:42:13
 * @FilePath: /c++/knowledge/入门到实战/charpter_07_函数/递归调用算年龄.cpp
 * @Description: 注释信息
 */

#include <iostream>

int age(int n)
{
    int f;
    if (n == 1)
    {
        f = 10;
    }
    else
    {
        f = age(n - 1) + 2;
    }
    return f;
}

int main(int argc, char *argv[])
{
    int i, j;

    printf("想知道年龄吗？请输入序号：\n");
    scanf("%d", &i);
    j = age(i);
    printf("他的年龄是%d\n", j);
}