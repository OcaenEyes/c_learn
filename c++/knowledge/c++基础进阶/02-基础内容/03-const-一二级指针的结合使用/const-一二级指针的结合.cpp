
#include <iostream>
#include <typeinfo>
/**
 * const 修饰的量 叫常量
 * 普通变量和常量的区别：1.编译方式不同， 2.不能作为左值
 * 
 * const 修饰的常量常出现的错误：
 * 1.常量不能作为左值 【即：直接修改常量的值会报错】
 * 2.不能把常量的地址 泄露给一个普通的指针 或 普通的引用变量 【即：间接修改常量的值会报错】
 * 
 * 
 * 
 * const 和一级指针的结合
 * const int*p;
 * int const *p;
 * int *const p;
 * const int *const p;
 * 
*/



int main()
{
    const int a = 10; //常量

    return 0; // success
}