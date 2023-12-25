

/**
 * 虚函数依赖：
 *  1）虚函数能产生地址，存储在vftable中
 *  2）对象必须存在（vfptr -> vftable）
 *
 * 1.哪些函数不能实现成虚函数？
 *  1）构造函数
 *  2）构造函数中调用任何函数都是静态绑定的
 *
 *  3）static静态成员方法
 *
 *
 * 2.虚析构函数： 析构函数调用的时候，对象是存在的
 *  1）什么时候需要把基类的析构函数实现为虚函数？？
 *     基类的指针pb（引用）指向了堆上 new出来的派生类对象； delete pb(基类的指针)，它在调用析构函数的时候，必须发生动态绑定，否则会导致派生类的析构函数无法调用
 *
 *
 */

#include <iostream>
#include <typeinfo>

class Base
{
private:
    int m_a;

public:
    Base(int data = 10) : m_a(data)
    {
        std::cout << "Base()" << std::endl;
    }

    void show()
    {
        std::cout << "Base::show()" << std::endl;
    }
    void show(int)
    {
        std::cout << "Base::show(int)" << std::endl;
        std::cout << "m_a = " << m_a << std::endl;
    }

    virtual ~Base()
    {
        std::cout << "～Base()" << std::endl;
    }
};

class Derived : public Base
{
private:
    int m_b;
    int *ptr;

public:
    Derived(int data = 20) : Base(data), m_b(data), ptr(new int(data))
    {
        std::cout << "Derived()" << std::endl;
    }

    void show()
    {
        std::cout << "Derived::show()" << std::endl;
    }

    // 基类的析构函数是virtual虚函数， 那么派生类的析构函数自动变成虚函数
    ~Derived()
    {
        delete ptr;
        std::cout << "～Derived()" << std::endl;
    }
};

int main()
{
    Derived d(10);
    d.show();

    Base *p = &d;
    p->show();

    Base *pb = new Derived(112);
    pb->show();

    // 此时只调用了基类的析构，但派生类的析构函数未被调用；
    // 需要将基类的析构函数 写成虚析构； 那么派生类的析构就自动变成虚析构，析构函数的调用就会变成动态绑定
    delete pb;

    return 0;
}