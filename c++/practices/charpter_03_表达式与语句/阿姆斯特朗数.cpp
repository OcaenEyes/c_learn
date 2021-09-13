#include <iostream>
using namespace std;

// 一个3位数，各位数字立方和 等于该数本身
int main()
{
    int i, j, k, n;
    for (i = 100; i < 1000; i++)
    {
        /* code */
        j = i % 10;
        k = i / 10 % 10;
        n = i / 100;

        if (j * j * j + k * k * k + n * n * n == i)
        {
            /* code */
            printf("%d \n", i);
        }
    }

    return 0;
}