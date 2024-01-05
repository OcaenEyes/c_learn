#include <iostream>
using namespace std;

// continue 跳过本次循环，并继续重新开始执行循环
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
            continue; // 跳过本次循环，并继续重新开始执行循环
        }
        sum = sum + n;
    }
    cout << "数的和是:" << sum << "\n";

    return 0;
}