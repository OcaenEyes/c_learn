#include <iostream>
using namespace std;

class printData
{
public:
    void print(int i)
    {
        cout << "整数为" << i << "\n";
    }

    void print(double d)
    {
        cout << "浮点数为" << d << "\n";
    }

    void print(char c[])
    {
        cout << "字符串为" << c << "\n";
    }
};

int main()
{
    printData pd;

    // 输出整数
    pd.print(5);
    // 输出浮点数
    pd.print(500.263);
    // 输出字符串
    char c[] = "Hello C++";
    pd.print(c);
    return 0;
}