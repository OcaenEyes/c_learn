#include <iostream>
using namespace std;

int main()
{
    int iInput;
    cout << "输入一个整数"
         << "\n";
    cin >> iInput;
    if (iInput % 2 != 0)
    {
        /* code */
        cout << "这是一个奇数"
             << "\n";
    }else{
        cout << "这是一个偶数"
             << "\n";
    }

    return 0;
}