#include <iostream>
using namespace std;

// 满足abcd=(ab+cd)^2的四位数
int main()
{
    int i, a, b;
    for (i = 1000; i < 10000; i++)
    {
        /* code */
        a = i / 100;
        b = i % 100;
        if ((a + b) * (a + b) == i)
        {
            /* code */
            printf("%d \n", i);
        }
    }

    return 0;
}