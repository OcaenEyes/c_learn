#include <iostream>
using namespace std;

int main()
{
    int i = 5, j = 8, k = 12, l = 4, x1, x2;
    x1 = i > j && k > l;
    x2 = !(i > j) && k > l;
    printf("x1: %d ,x2: %d", x1, x2);
    return 0;
}