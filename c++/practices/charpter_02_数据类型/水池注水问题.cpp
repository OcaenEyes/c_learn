#include <iostream>
using namespace std;

int main()
{
    float a1 = 3, b1 = 1, c1 = 4, d1 = 5;
    float day;
    day = 1 / (1 / a1 + 1 / b1 + 1 / c1 + 1 / d1);
    printf("需要 %f 天！\n", day);
    return 0;
}