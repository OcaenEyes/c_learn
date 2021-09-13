#include <iostream>
using namespace std;

// break 跳出循环体，从而中断当前循环
int main()
{
    int i, n, sum;
    sum = 0;
    cout << "请输入10个整数"
         << "\n";
    for (i = 1; i <= 10; i++)
    {
        /* code */
        cout << i << ":";
        cin >> n;
        if (n < 0)
        {
            /* code */
            break; // 不累加复数，并跳出循环
        }
        sum = sum + n;
    }
    cout << "数的和是:" << sum << "\n";

    return 0;
}