/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 14:53:23
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 15:18:21
 * @FilePath: /c++/knowledge/c++基础进阶/07-继承与多态-多重继承/03-四种类型转换方式.cpp
 * @Description: 注释信息
 *
 */

/**
 * int a = (int)b;
 *
 * c++ 四种类型转换方法
 *
 *  1. const_cast :  去掉常量属性的类型转换
 *      const_cat<这个尖括号内必须是指针后引用 int* int&>
 *  2. static_cast : 提供编译器认为安全的类型转换( 不允许没有任何联系的类型之间的转换 )--编译时期的类型转换
 *      基类 <<===>> 派生类，之间可以使用static_cast互相强转
 *  3. reinteroret_cast : 类似于C风格的强制类型转换
 *      不安全，强制转换
 *  4. dynamic_cast : 主要用在继承结构中，可支持RTTI类型识别的上下转换---运行时期的类型转换
 *
 *
 *
 */
#include <iostream>

class Base
{
public:
    virtual void func() = 0;
};

class Derivel1 : public Base
{
public:
    void func() override
    {
        std::cout << "Derivel1 func()" << std::endl;
    }
};

class Derivel2 : public Base
{
public:
    void func() override
    {
        std::cout << "Derivel2 func()" << std::endl;
    }

    void derivel2Func()
    {
        std::cout << "Derivel2 derivel2Func()" << std::endl;
    }
};

void showFunc(Base *base)
{
    // dynamic_cast会检查base指针 指向的是否 是一个类型的对象
    // 如果不是，返回NULL/nullptr
    // 如果是，返回指向该对象的指针

    Derivel2 *pd2 = dynamic_cast<Derivel2 *>(base);
    if (pd2 != nullptr)
    {
        pd2->derivel2Func();
    }
    else
    {
        base->func(); // 会动态绑定
    }
}

int main()
{
    const int a = 10;
    int *p1 = (int *)a;

    // const_cast
    int *p2 = const_cast<int *>(&a); // 语言级别，原类型需要跟转换后类型一样

    // static_cast
    int *p = nullptr;
    // short *p3 = static_cast<short *>(p); // 强转无效

    // reinteroret_cast 强制转换
    double *p4 = reinterpret_cast<double *>(p); // 可转换但不安全

    // dynamic_cast
    Derivel1 d1;
    Derivel2 d2;

    showFunc(&d1);
    showFunc(&d2);

    return 0;
}