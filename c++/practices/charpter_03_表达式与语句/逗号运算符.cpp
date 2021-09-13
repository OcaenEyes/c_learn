#include <iostream>
using namespace std;

int main()
{
    int a = 4, b = 6, c = 8, res1, res2;
    res1 = a, res2 = b + c;
    for (int i = 0; i < 2; i++)
    {
        /* code */
        printf("***********\n");
        printf("y= %d, x=%d \n", res1, res2);
    }

    return 0;
}