#include <iostream>
using namespace std;

int main()
{
    int i, x, y, z = 1;
    printf("请输入两个数，x 和 y, (x^y):\n");
    scanf("%d, %d", &x, &y);
    for (int i = 1; i < y; i++)
    {
        /* code */
        z = z * x % 1000;
    }
    if (z >= 100)
    {
        /* code */
        printf("%d ^ %d的最后位是：%d\n", x, y, z);
    }
    else
    {
        printf("%d ^ %d的最后位是：0%d\n", x, y, z);
    }

    return 0;
}