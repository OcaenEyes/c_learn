// #include "pch.h"
#include <iostream>

/**
 * 1. main函数调用sum, sum执行完以后，怎么知道回到哪个函数中？
 * 2. sum函数执行完，回到main以后，怎么知道从哪一行指令继续运行？
 *
 */

int sum(int a, int b)
{
    int temp = 0;
    temp = a + b;
    return temp;
}

int main()
{
    int a = 10; // mov dword ptr[ebp-4],0Ah
    int b = 20; // mov dword ptr[ebp-8],14h
    int ret = sum(a, b);

    std::cout << ret << "\n";
    return 0;
}