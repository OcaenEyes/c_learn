#include <iostream>
using namespace std;

int main()
{
    char c1, c2;
    printf("输入一个小写字符\n");
    c1 = getchar();
    c2 = c1 - 32;
    printf("转换后的字符：%c , %d \n", c2, c2);
    return 0;
}