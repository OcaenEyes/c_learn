
/**
 * 1.重载关系：
 *  一组函数要重载，必须处在同一个作用域当中；而且函数名相同，参数列表不同
 *
 * 2.隐藏关系：
 *  在继承结构中，派生类的同名成员，把基类的同名成员隐藏了
 *
 *
 * =============================================================
 * 1.把继承结构，也说成从上（基类）到下（派生类）的结构
 * 2.
 *
 * 基类对象-->派生类对象
 * 派生类对象--->基类对象
 *
 *
 * 基类指针（引用） --->派生类对象
 * 派生类指针(引用) ---> 基类对象
 *
 * 总结：在继承中，默认的类型转换 只能从下到上的转换
 */

#include <iostream>

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

    ~Base()
    {
    }
};

class TestO1 : public Base
{
public:
    TestO1(int data = 10) : Base(data),
                            m_b(data) {}

    void show()
    {
        std::cout << "TestO1::show()" << std::endl;
    }
    void show(int)
    {
        std::cout << "TestO1::show(int)" << std::endl;
        std::cout << "m_b = " << m_b << std::endl;
    }

private:
    int m_b;
};

int main()
{
    TestO1 test(10);
    test.show();
    test.show(10);

    Base b(10);
    TestO1 t(20);

    b = t; // 基类对象b <<--派生类对象t     类型从下到上的转换            true

    // t = b; // 派生类对象t <<-- 基类对象b    类型从上到下的转换            false

    Base *pb = &t; // 基类指针（引用） <<-- 派生类对象      类型从下到上的转换            true

    // TestO1 *pt = &pb; // 派生类指针(引用)  <<-- 基类对象    类型从上到下的转换            false

    return 0;
}