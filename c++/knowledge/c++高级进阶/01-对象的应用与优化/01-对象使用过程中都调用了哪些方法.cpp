/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 03:01:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 03:17:06
 * @FilePath: /c++/knowledge/c++高级进阶/01-对象的应用与优化/01-对象使用过程中都调用了哪些方法.cpp
 * @Description: 注释信息
 *
 */

#include <iostream>

class Test
{
private:
    int m_a;

public:
    Test(int a = 10) : m_a(a)
    {
        std::cout << "Test(int a = 10)!\n";
    }

    ~Test()
    {
        std::cout << "~Test()!\n";
    }

    Test(const Test &t) : m_a(t.m_a)
    {
        std::cout << "Test(const Test &t)!\n";
    }

    Test &operator=(const Test &t)
    {
        std::cout << "Test &operator=(const Test &t)!\n";
        m_a = t.m_a;
        return *this;
    }
};

int main()
{
    Test t1;      // 构造
    Test t2(t1);  // 拷贝构造
    Test t3 = t1; // 拷贝构造

    // Test(20)显式生成临时对象， 生存周期：所在的语句
    // c++编译器 对于 对象构造的优化：用临时变量生成新对象时，临时对象就不产生了，直接构造新对象就可以了
    Test t4 = Test(20); // 与 Test t4(20);没有区别

    std::cout << "=====================\n";

    t4 = t2;
    //  t4.operator=(const Test &t)
    t4 = Test(30); // 此时Test(30) 生成临时变量是会执行的； 显式生成临时对象，再调用赋值函数
    t4 = (Test)30; // int 强制转换为 Test类型， 查找有木有int参数的构造函数；   显式生成临时对象，再调用赋值函数

    std::cout << "=====================\n";
    t4 = 40; // 隐式生成临时对象，再调用赋值函数

    std::cout
        << "=====================\n";

    Test *p = &Test(50);
    // p指向的是一个已经析构的临时对象， 此时就会异常。是不安全的！！！！！
    p = nullptr;

    const Test &ref = Test(51);

    std::cout
        << "=====================\n";

    return 0;
}
