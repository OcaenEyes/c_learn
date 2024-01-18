/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 04:06:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 07:16:25
 * @FilePath: /c++/knowledge/c++高级进阶/02-智能指针/01-shared_pt的交叉引用问题.cpp
 * @Description: 注释信息
 */

/**
 * @brief
 *  强智能指针的循环引用问题：
 *      1. 造成new出来的资源无法释放
 *  解决方法：
 *      1.定义对象的时候用强智能指针，  shared_ptr  可以改变资源的引用计数
 *      2.引用对象的地方使用弱智能指针,  weak_ptr  不会改变资源的引用计数
 *
 *
 */

#include <memory>
#include <iostream>

class B;
class A
{
private:
public:
    A(/* args */) { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }
    std::weak_ptr<B> ptrb_; // 引用的地方

    void testA() { std::cout << "测试一下A吧\n"; }
};

class B
{
private:
public:
    B(/* args */) { std::cout << "B()\n"; }
    ~B() { std::cout << "~B()\n"; }
    std::weak_ptr<A> ptra_; // 引用的地方

    void func()
    {
        std::shared_ptr<A> p_s = ptra_.lock(); // 将弱指针 提升为 强指针
        if (p_s != nullptr)
        {
            // 提升成功
            p_s->testA();
        }
    }
};

int main()
{
    std::shared_ptr<A> p_a(new A()); // 定义的地方
    std::shared_ptr<B> p_b(new B()); // 定义的地方

    p_a->ptrb_ = p_b;
    p_b->ptra_ = p_a;

    std::cout << "p_a.use_count()" << p_a.use_count() << "\n";
    std::cout << "p_b.use_count()" << p_b.use_count() << "\n";

    p_b->func();

    return 0;
}