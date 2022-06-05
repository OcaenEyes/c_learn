// 指针是一个变量，其值为另一个变量的地址，即，内存位置的直接地址
// 声明指针
// type *var-name

#include <iostream>
using namespace std;

int nullpointer();

int main()
{
    int var1 = 20;
    int *ip;
    //  在指针变量中存储var1的地址
    ip = &var1;

    // 输出在指针变量中存储的地址
    cout << ip << endl;
    // 访问指针中地址的值
    cout << *ip << endl;
    //输出var1的值
    cout << var1 << endl;

    int arr[5] = {1, 2, 3, 4, 5};
    int *ip1 = arr;
    cout << arr << "\n";
    cout << ip1 << "\n";
    cout << &arr << "\n";
    cout << "*ip1: " << *ip1 << "\n";
    int i = nullpointer();

    // system("pause");
    return 0;
}

// int    *ip;    /* 一个整型的指针 */
// double *dp;    /* 一个 double 型的指针 */
// float  *fp;    /* 一个浮点型的指针 */
// char   *ch;    /* 一个字符型的指针 */

int nullpointer()
{
    int *ptr = NULL;
    cout << "ptr的值是" << ptr << "\n";

    if (ptr)
    {
        cout << "ptr 非空 not null"
             << "\n";
    }

    if (!ptr)
    {
        cout << "ptr 空 is null"
             << "\n";
    }

    return 0;
}

/*

概念	描述
C++ Null 指针	C++ 支持空指针。NULL 指针是一个定义在标准库中的值为零的常量。
C++ 指针的算术运算	可以对指针进行四种算术运算：++、--、+、-
C++ 指针 vs 数组	指针和数组之间有着密切的关系。
C++ 指针数组	可以定义用来存储指针的数组。
C++ 指向指针的指针	C++ 允许指向指针的指针。
C++ 传递指针给函数	通过引用或地址传递参数，使传递的参数在调用函数中被改变。
C++ 从函数返回指针	C++ 允许函数返回指针到局部变量、静态变量和动态内存分配。

*/