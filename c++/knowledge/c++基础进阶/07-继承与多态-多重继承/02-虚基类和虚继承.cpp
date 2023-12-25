
/**
 * 多重继承：代码复用， 一个派生类有多个基类
 *  class C: public A,public B{
 *
 *  };
 *
 *
 * 抽象类：有纯虚函数的类
 *
 * virtual:
 *  1.修饰成员方法： 虚函数
 *  2.修饰继承方式：虚继承； 被虚继承的类，称作虚基类
 *
 * 虚基类：
 */
#include <iostream>

class A
{
private:
    int ma;

public:
    virtual void func()
    {
        std::cout << "A::func" << std::endl;
    }

    void operator delete(void *p)
    {
        std::cout << "operator delete" << p << std::endl;
        // ::delete [] (char *)p;
        free(p);
    }

public:
};

class B : virtual public A
{
private:
    int mb;

public:
    void func() override
    {
        std::cout << "B::func" << std::endl;
    }

    void *operator new(size_t size)
    {

        std::cout << "operator new" << std::endl;
        // return ::new char[size];
        return malloc(size);
    }
};

int main()
{

    //  基类指针指向派生类， 永远指向的是派生类对象【起始内存】内存的首地址
    B b;
    A *p = &b;
    // A *p = new B();
    p->func();
    // delete p;

    return 0;
}