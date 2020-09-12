#include <iostream>
#include <cmath>
using namespace std;

int main(){
    //数字定义
    short s;
    int i ;
    long l;
    float f;
    double d;


    //数字赋值
    s = 10;
    i = 100;
    l = 1000000;
    f = 230.47;
    d = 30949.374;

    //数字输出
    cout << s << endl;
    cout << i << endl;
    cout << l << endl;
    cout << f << endl;
    cout << d << endl;

    //数学运算
    cout << "sin  正弦" << sin(d)  << endl;
    cout << "abs  绝对值" << abs(i)  << endl;
    cout << "floor 小于等于参数的最大整数" << floor(d)  << endl;
    cout << "sqrt 算术平方根" << sqrt(f)  << endl;
    cout << "pow ，x的y次方" << pow(i,2)  << endl;
    cout << "cos 余弦 " << cos(d)  << endl;


    //随机数
    int k;
    //设置种子
    srand( (unsigned) time(NULL));
    /* 生成10个随机数*/
    for (int i = 0 ; i < 10; i++)
    {
        /* code */
        k = rand();
        cout << "随机数" << k << endl;

    }
    


    return 0;
}

/*
数学运算
序号	函数 & 描述
1	double cos(double); 该函数返回弧度角（double 型）的余弦。
2	double sin(double); 该函数返回弧度角（double 型）的正弦。
3	double tan(double); 该函数返回弧度角（double 型）的正切。
4	double log(double); 该函数返回参数的自然对数。
5	double pow(double, double); 假设第一个参数为 x，第二个参数为 y，则该函数返回 x 的 y 次方。
6	double hypot(double, double); 该函数返回两个参数的平方总和的平方根，也就是说，参数为一个直角三角形的两个直角边，函数会返回斜边的长度。
7	double sqrt(double); 该函数返回参数的平方根。
8	int abs(int); 该函数返回整数的绝对值。
9	double fabs(double); 该函数返回任意一个浮点数的绝对值。
10	double floor(double); 该函数返回一个小于或等于传入参数的最大整数。

*/