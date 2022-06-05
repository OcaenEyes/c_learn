#include <iostream>
using namespace std;

/**
 * @brief
 * 1.有参函数和无参函数
 * 2.有返回值函数和无返回值函数
 * 3.主函数 main
 * 4.函数的定义和调用
 *
 */

/**
 * @brief
 *
 * @param x
 * @param y
 * @return int
 */

int mul(int x, int y)
{
    return x * y;
}

int main()
{
    int a, b, c;
    printf("请输入两个整数:\n");
    scanf("%d%d", &a, &b);
    c = mul(a, b);
    printf("两数之积是: %d", c);
    return 0;
}