#include <iostream>
using namespace std;

int main()
{
    int ivar = 0;
    int num = 0;
label:
    ivar++;
    num += ivar;
    if (ivar < 10)
    {
        /* code */
        goto label;
    }
    cout << num << "\n";

    return 0;
}