#include <iostream>
using namespace std;

// 变量声明
extern int a,b;
extern int c;
extern float f;

// 全局变量
int e;
// 全局变量未赋值时，则会自动初始化
// 数据类型	初始化默认值
// int	0
// char	'\0'
// float	0
// double	0
// pointer	NULL

//函数声明
int func();

int main(){
    //变量定义
    int a,b;
    int c;
    float f;


    // 局部变量
    int d;

    //在函数内，局部变量的值会覆盖全局变量的值

    // 变量初始化
    a=10;
    b=20;
    c =a+b;
    cout << c <<endl;

    f = 70.0 /3.0;
    cout << f << endl;

    // 函数调用
    int i = func();

    return 0;
}


//函数定义
int func(){
    return 0;
}

