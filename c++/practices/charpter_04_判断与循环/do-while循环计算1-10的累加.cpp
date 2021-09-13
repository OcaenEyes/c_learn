#include <iostream>
using namespace std;

int main()
{
    int sum = 0, i = 1;
    do
    {
        /* code */
        cout << "第" << i << "次 \n";
        sum = sum + i;
        i++;
        cout << "i:" << i
             << "\n";
    } while (/* condition */ i <= 10);
    cout << "sum:" << sum << "\n";

    return 0;
}