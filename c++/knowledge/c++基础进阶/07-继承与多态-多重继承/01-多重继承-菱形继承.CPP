/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 14:19:11
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 14:29:39
 * @FilePath: /c++/knowledge/c++基础进阶/07-继承与多态-多重继承/01-多重继承-菱形继承.CPP
 * @Description: 注释信息
 */

/**
 * c++的的多重继承 -- 菱形继承
 *  1. 采用虚基类来解决
 *
 * 好处：可以做更多代码的复用 D 继承自B，C； B*p = new D(); C*p = new D();
 *
 */

#include <iostream>

class A
{
private:
protected:
    int ma;

public:
    A(int data = 0) : ma(data)
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

class B : virtual public A // 采用虚继承
{
protected:
    int mb;

public:
    B(int data = 0) : A(data), mb(data)
    {
        std::cout << "B()" << std::endl;
    }
    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
};

class C : virtual public A // 采用虚继承
{
protected:
    int mc;

public:
    C(int data = 0) : A(data), mc(data)
    {
        std::cout << "C()" << std::endl;
    }
    ~C()
    {
        std::cout << "~C()" << std::endl;
    }
};

class D : public B, public C // B，C采用虚继承，此时可以解决构造两次A的问题
{
protected:
    int md;

public:
    D(int data = 0) : A(data), B(data), C(data), md(data) // A 直接由D构造
    {
        std::cout << "D()" << std::endl;
    }
    ~D()
    {
        std::cout << "~D()" << std::endl;
    }
};

int main()
{
    D d(10);
    return 0;
}