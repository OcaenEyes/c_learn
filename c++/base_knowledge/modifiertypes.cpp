#include <iostream>
using namespace std;

// 修饰符类型
/*
修饰符 signed、unsigned、long 和 short 可应用于整型，
signed 和 unsigned 可应用于字符型，
long 可应用于双精度型。

修饰符 signed 和 unsigned 也可以作为 long 或 short 修饰符的前缀

*/




int main(){
    short int i;   // 有符号短整数
    short unsigned int j;   //无符号短整数

    j = 50000;
    i =j ;
    cout << i << " " << j;

    system("pause");
    return 0;
}