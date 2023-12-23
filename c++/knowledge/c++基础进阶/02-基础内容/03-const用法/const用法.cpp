#include <iostream>
#include <typeinfo>
#include <stdio.h>

/**
 * const修饰的变量，不能再作为左值，初始化后不能再被修改
 * C语言中：const修饰的量，可以不用初始化； 不叫常量，叫常变量
 * C++语言中：const修饰的量，必须初始化；叫常量
 */

void test01()
{
    const int a = 10; // 常量

    int array[a] = {};

    int *p = (int *)&a;
    *p = 30; // 可以修改a对应的内存上存储的数据

    // 20 30 20
    printf("%d %d %d \n", 20, *p, 20);
}

void test02()
{
    int b = 10;
    const int a = b; // 常变量
    int array[b] = {}; 

    int *p = (int *)&a;
    *p = 30; // 可以修改a对应的内存上存储的数据

    // 20 30 20
    printf("%d %d %d \n", 20, *p, 20);
}

int main()
{
    return 0;
}