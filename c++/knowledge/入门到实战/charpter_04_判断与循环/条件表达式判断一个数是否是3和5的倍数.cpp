#include <iostream>
using namespace std;

int main()
{
    int iInput;
    cout << "输入一个整数"
         << "\n";
    cin >> iInput;
    (iInput % 3 == 0 && iInput % 5 == 0) ? cout << "是" : cout << "否";
    cout << "\n";
    return 0;
}