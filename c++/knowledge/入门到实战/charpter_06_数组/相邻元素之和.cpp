#include <iostream>
using namespace std;

int main()
{
    int a[5], b[5], i;
    printf("请输入一个数组 \n");
    for (int i = 0; i < 5; i++)
    {
        /* code */
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < 5; i++)
    {
        /* code */
        b[i] = a[i] + a[i - 1];
    }

    for (int i = 1; i < 5; i++)
    {
        /* code */
        printf("%5d", b[i]);
    }
    printf("\n");

    return 0;
}