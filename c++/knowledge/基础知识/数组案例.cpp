#include <iostream>
using namespace std;

int pigweight();

int main()
{
    int i = pigweight();
    cout << i << "\n";
    return 0;
}

// 案例一
// 5只小猪称体重,体重最大的那个猪
int pigweight()
{
    int arr[5] = {330, 360, 200, 400, 250};
    int maxweight = 0;
    for (int i : arr)
    {
        if (/* condition */ i > maxweight)
        {
            /* code */
            maxweight = i;
        }
    }
    return maxweight;
}