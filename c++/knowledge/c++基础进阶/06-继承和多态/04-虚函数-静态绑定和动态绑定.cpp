/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 06:30:50
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 08:21:47
 * @FilePath: /c++/knowledge/c++基础进阶/06-继承和多态/04-虚函数-静态绑定和动态绑定.cpp
 * @Description: 注释信息
 */

/**
 * 1.含有虚函数的类是可以被实例化
 * 2.含有纯虚函数的类是不可以被实例化的，必须被继承，才能够被实例化
 *
 * 覆盖：
 *   如果派生类中的方法，和基类继承来的某个方法， 返回值、函数名、参数列表都相同； 而且基类的方法是虚函数，那么派生类的这个方法自动处理成虚函数

 * 
 *
 * 总结：
 *  1.如果类内定义了虚函数，那么在编译阶段，编译器需给这个类类型产生唯一的vftable【虚函数表】
 *     1）虚函数表里重要存储的是【RTTI指针】run time type information 运行时的类型信息、【虚函数地址】
 *     2）当程序运行时，每一张虚函数表都会加载到内存的.rodata区
 *
 *  2.一个类内定义了虚函数，那么这个类定义的对象，在运行时，内存中开始部分多存储一个vfptr虚函数指针， 指向相应类型的虚函数vftable
 *     1）一个类型定义的N个对象，他们的vfptr指向的都是同一张虚函数表
 *
 *  3.一个类里面的虚函数个数，不影响对象内存大小(vfptr)， 影响的是虚函数表的大小(vftable)
 */

#include <iostream>
#include <typeinfo>

class Base
{
private:
    int m_a;

public:
    Base(int data = 10) : m_a(data) {}

    void show()
    {
        std::cout << "Base::show()" << std::endl;
    }
    void show(int)
    {
        std::cout << "Base::show(int)" << std::endl;
        std::cout << "m_a = " << m_a << std::endl;
    }

    // 虚函数
    virtual void virshow()
    {
        std::cout << "Base::virshow()" << std::endl;
    }

    // 虚函数
    virtual void virshow(int)
    {
        std::cout << "Base::virshow(int)" << std::endl;
    }

    ~Base()
    {
    }
};

class Derived : public Base
{
private:
    int m_b;

public:
    Derived(int data = 20) : Base(data), m_b(data) {}

    void show()
    {
        std::cout << "Derived::show()" << std::endl;
    }

    // 如果派生类中的方法，和基类继承来的某个方法， 返回值、函数名、参数列表都相同； 而且基类的方法是虚函数，那么派生类的这个方法自动处理成虚函数
    // 重写 <==> 覆盖 【覆盖重写了virshow函数】
    void virshow() // 被自动处理为虚函数
    {
        std::cout << "Derived::virshow()" << std::endl;
    }

    ~Derived()
    {
    }
};

int main()
{
    Derived d(50);
    Base *p = &d;

    p->virshow(); // 发现virshow是虚函数，进行动态绑定 动态（运行期间）绑定（函数的调用），调用的是Derived::virshow()

    p->show();    // 静态绑定 静态（编译期间）绑定（函数的调用），调用的是Base::show()
    p->show(100); // 静态绑定 静态（编译期间）绑定（函数的调用），调用的是Base::show(int)

    std::cout << "sizeof(Base) = " << sizeof(Base) << std::endl;       // 4
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << std::endl; // 8

    std::cout << "typeid(p).name() = " << typeid(p).name() << std::endl;
    std::cout << "typeid(*p).name() = " << typeid(*p).name() << std::endl;
    std::cout << "typeid(d).name() = " << typeid(d).name() << std::endl;

    Derived dd(20);
    dd.show();
    dd.virshow();
    return 0;
}
