/*
引用 vs 指针
1、不存在空引用。引用必须连接到一块合法的内存。
2、一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
3、引用必须在创建时被初始化。指针可以在任何时间被初始化。
*/

#include <iostream>
using namespace std;

int main(){
    // 声明简单的变量
    int i;
    double d;

    // 声明引用变量
    int& r = i;
    double& s = d;

    i = 5;
    cout << "i value " << i << "\n";
    cout << "r  reference vale" << r << "\n";

    d = 11.6;
    cout << "d value " << d << "\n";
    cout << "s  reference vale" << s << "\n";

    return 0;
}

/*
概念	描述
把引用作为参数	C++ 支持把引用作为参数传给函数，这比传一般的参数更安全。
把引用作为返回值	可以从 C++ 函数中返回引用，就像返回其他数据类型一样。
*/