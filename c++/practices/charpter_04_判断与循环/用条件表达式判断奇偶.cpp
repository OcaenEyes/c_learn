#include <iostream>
using namespace std;

int main()
{
    int iInput;
    cout << "输入一个整数"
         << "\n";
    cin >> iInput;
    cout << iInput % 2 << "\n";
    (iInput % 2 == 0) ? cout << "这个数是偶数 \n" : cout << "这个数是奇数 \n";
    return 0;
}