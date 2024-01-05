#include <iostream>
using namespace std;

int main()
{
    char iInput;
    cin >> iInput;
    switch (iInput)
    {
    case 'A':
        /* code */
        cout << "非常好"
             << "\n";
        break;
    case 'B':
        /* code */
        cout << "好"
             << "\n";
        break;
    case 'C':
        /* code */
        cout << "一般"
             << "\n";
        break;
    case 'D':
        /* code */
        cout << "差"
             << "\n";
        break;

    default:
        break;
    }
    return 0;
}