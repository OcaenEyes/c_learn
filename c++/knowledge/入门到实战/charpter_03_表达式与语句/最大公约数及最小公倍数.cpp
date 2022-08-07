#include <iostream>
using namespace std;

// 两数乘积 除以两数的最大公约数 就是他们的最小公倍数
int main()
{
    int a, b, c, m, t;
    printf("请输入两个数字：\n");
    scanf("%d, %d", &a, &b);
    if (a < b)
    {
        /* code */
        t = a;
        a = b;
        b = t;
    }
    m = a * b;
    c = a % b;
    while (c != 0)
    {
        /* code */
        a = b;
        b = c;
        c = a % b;
    }
    printf("最大公约数： \n %d \n", b);
    printf("最小公倍数：\n %d \n", m / b);

    return 0;
}