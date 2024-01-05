#include <iostream>
using namespace std;

int main()
{
    float a, b;
    char c;
    printf("请输入运算格式：a(+,-,*,/)b \n");
    scanf("%f %c %f", &a, &c, &b);
    switch (c)
    {
    case '+':
        printf("%f \n", a + b);
        break;
    case '-':
        printf("%f \n", a - b);
        break;
    case '*':
        printf("%f \n", a * b);
        break;
    case '/':
        if (b == 0)
        {
            printf("除数不能是0 \n");
        }
        else
        {
            printf("%f \n", a / b);
        }
        break;

    default:
        break;
    }
    return 0;
}