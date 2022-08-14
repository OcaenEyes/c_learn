/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 12:14:17
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 12:18:44
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/输出指针运算后的地址值.cpp
 * @Description: 注释信息
 */
#include <iostream>

int main(int argc, char *argv[])
{
    int a = 100;
    int *p = &a;
    int *p1;
    p1 = &a;

    printf("p地址是：%d\n", p);
    p++;
    printf("p++地址是：%d\n", p);
    p--;
    printf("p--地址是：%d\n", p);

    printf("p1地址是：%d\n", p1);
    std::cout << "指针p对应的数值" << (*p) << std::endl;
    std::cout << "指针p1对应的数值" << (*p1) << std::endl;
    return 0;
}