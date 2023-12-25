/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 11:51:34
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 11:58:24
 * @FilePath: /c++/knowledge/c++基础进阶/06-继承和多态/07-虚函数和动态绑定.cpp
 * @Description: 注释信息
 */

/**
 * 虚函数和动态绑定，问题：是不是虚函数的调用一定是动态绑定？ 答案：肯定不是
 *
 * 在类的构造函数中，调用虚函数，也是静态绑定
 *
 * 动态绑定：必须是指针、引用变量调用虚函数
 *
 *
 */

#include <iostream>

class Base
{
protected:
    int ma;

public:
    Base(int data) : ma(data)
    {
        std::cout << "Base(int data)" << std::endl;
    }
    ~Base()
    {
        std::cout << "~Base()" << std::endl;
    }

    virtual void show()
    {
        std::cout << "Base::show()" << std::endl;
    }
};

class Derived : public Base
{
public:
    Derived(int data) : Base(data)
    {
        std::cout << "Derived(int data)" << std::endl;
    }

    ~Derived()
    {
        std::cout << "~Derived()" << std::endl;
    }

    void show() override
    {
        std::cout << "Derived::show()" << std::endl;
    }
};

int main()
{
    Base b(10);
    Derived d(20);

    b.show(); // 对象本身调用虚函数，是静态绑定
    d.show(); // 对象本身调用虚函数，是静态绑定
    std::cout << "--------------------" << std::endl;

    Base *pb = &b;
    pb->show(); // 对象指针调用虚函数，是动态绑定

    Base *pd = &d;
    pd->show(); // 对象指针调用虚函数，是动态绑定

    Base &rb = b;
    rb.show(); // 对象引用调用虚函数，是动态绑定

    Base &rd = d;
    rd.show(); // 对象引用调用虚函数，是动态绑定

    return 0;
}