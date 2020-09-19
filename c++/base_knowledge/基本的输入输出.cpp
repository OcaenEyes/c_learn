// 输入操作
// 如果字节流是从设备（如键盘、磁盘驱动器、网络连接等）流向内存，这叫做输入操作

// 输出操作
// 如果字节流是从内存流向设备（如显示屏、打印机、磁盘驱动器、网络连接等），这叫做输出操作

/*
头文件	函数和描述
<iostream>	该文件定义了 cin、cout、cerr 和 clog 对象，分别对应于标准输入流、标准输出流、非缓冲标准错误流和缓冲标准错误流。
<iomanip>	该文件通过所谓的参数化的流操纵器（比如 setw 和 setprecision），来声明对执行标准化 I/O 有用的服务。
<fstream>	该文件为用户控制的文件处理声明服务。我们将在文件和流的相关章节讨论它的细节。
*/

// 标准输出流 cout
// 标准输入流 cin
// 标准错误流 cerr
// 标准日志流 clog

#include <iostream>
#include <string>
using namespace std;

int shuchu();
int shuru();
int cuowu();
int rizhi();

int main()
{
    int i = shuchu();
    int j = shuru();
    int k = cuowu();
    int l = rizhi();
    return 0;
}

int shuchu()
{
    string i = "hello c++";
    cout << "输出语句"
         << "\n";
    cout << "i value is" << i << "\n";
    return 0;
}

int shuru(){
    string i;
    cout << "请输入你的姓名" << "\n";
    cin >> i;
    cout << "您输入的姓名是：" << i << "\n";

    return 0;
}

int cuowu(){
    string i = "出现错误了";

    cerr << "Error message:" <<i << "\n";
    return 0;
}

int rizhi(){
    string i = "这是一个日志";

    cerr << "Log message:" <<i << "\n";
    return 0;
}