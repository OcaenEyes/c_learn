#include <iostream>
using namespace std;

// 普通闰年：公历年份是4的倍数，且不是100的倍数的，为闰年（如2004年、2020年等就是闰年）。
// 世纪闰年：公历年份是整百数的，必须是400的倍数才是闰年（如1900年不是闰年，2000年是闰年）。

int pd01()
{
    int iYear;
    cout << "请输入年份"
         << "\n";
    cin >> iYear;
    if (iYear % 4 == 0)
    {
        /* code */
        if (iYear % 100 == 0)
        {
            if (iYear % 400 == 0)
            {
                cout << "这是闰年"
                     << "\n";
            }
            else
            {
                cout << "这不是闰年"
                     << "\n";
            }
        }
        else
        {
            cout << "这是闰年"
                 << "\n";
        }
    }
    else
    {
        cout << "这不是闰年"
             << "\n";
    }

    return 0;
}

int pd02()
{
    int iYear;
    cout << "请输入年份"
         << "\n";
    cin >> iYear;
    if (iYear % 4 == 0 && iYear % 100 != 0 || iYear % 400 == 0)
    {
        /* code */
        cout << "这是闰年"
             << "\n";
    }
    else
    {
        cout << "这不是闰年"
             << "\n";
    }
    return 0;
}

int main()
{
    pd01();
    pd02();
    return 0;
}