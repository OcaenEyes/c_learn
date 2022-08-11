/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 00:37:21
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-12 01:05:40
 * @FilePath: /c++/practices/rtti_demo/src/test.cpp
 * @Description: 注释信息
 */
#include <iostream>

struct V
{
    virtual void f(){};
};

struct A : virtual V
{
};
struct B : virtual V
{
    B(V *v, A *a)
    {
        // 在构造时进行转换
        dynamic_cast<B *>(v); // 明确定义的:v 的类型是V*, V是B的基类， 结果是B*
        dynamic_cast<B *>(a); // 未定义行为： a 的类型未A* ，A不是B的基类
    }
};

struct D : A, B
{
    D() : B((A *)this, this){};
};

struct Base
{
    virtual ~Base(){};
};

struct Derived : Base
{
    virtual void name(){};
};
int main()
{
    D d;                             //派生类对象
    A &a = d;                        // upcast
    D &new_d = dynamic_cast<D &>(a); // downcast
    B &new_b = dynamic_cast<B &>(a); // sidecast

    Base *b1 = new Base;
    if (Derived * d = dynamic_cast<Derived *>(b1))
    {
        std::cout << "从b1到d的 downcast" << std::endl;
        d->name(); // 安全调用
    }

    Base *b2 = new Derived;
    if (Derived * d = dynamic_cast<Derived *>(b2))
    {
        std::cout << "从b2到d的 downcast" << std::endl;
        d->name(); // 安全调用
    }

    delete b1;
    delete b2;

    return 0;
}

/**
 * 上面的代码只会输出 b2 到 d 的 downcast。
 * 首先我们定义了一个 D 类型的派生类对象，D 派生自 A 和 B。然后用一个 A 类型的引用去应用了一个 D 类型的对象，这就是典型的 upcast。
 * 而如果我们将 A 类型的引用使用 dynamic_cast 转换为其子类对象的引用，这就是典型的 downcast。
 * 而如果我们把一个引用 D 类对象的父类 A 引用转换为 D 类对象的另一个父类 B 的引用，这就是 sidecast。
 * 接着，b1 是一个基类指针，指向了一个基类的对象，如果我们把它在运行时视为一个子类对象，而去调用子类对象的方法，这是不安全的调用，因此从 b1 到 d 的 downcast 是不会成功的。
 * 而对于 b2 来说，b2 也是一个基类指针，但其指向的是一个派生类的对象，我们是能够通过 dynamic_cast 安全的将其转换成一个派生类指针，从而成功调用派生类的方法。
*/