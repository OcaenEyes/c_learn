#include <iostream>
using namespace std;

int main()
{
    int i, j, a[][3] = {3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}