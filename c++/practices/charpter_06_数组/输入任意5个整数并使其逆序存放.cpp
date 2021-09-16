#include <iostream>
using namespace std;

int main()
{
    int a[5], i, temp;
    printf("请输入数组 a: \n");
    for (int i = 0; i < 5; i++)
    {
        /* code */
        scanf("%d", &a[i]);
    }
    printf("数组a为: \n");
    for (int i = 0; i < 5; i++)
    {
        /* code */
        printf("%d", a[i]);
    }
    printf("\n");

    for (int i = 0; i < 2; i++)
    {
        /* code */
        temp = a[i];
        a[i] = a[4 - i];
        a[4 - i] = temp;
    }
    printf("新数组a为: \n");
    for (int i = 0; i < 5; i++)
    {
        /* code */
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}