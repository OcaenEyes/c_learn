
/**
 * @brief
 *  1. 函数参数传递过程中，对象优先按照引用传递， 不要按值传递
 *  2. 函数返回对象的时候，应该优先返回一个临时对象， 而不是返回一个定义过的对象
 *  3. 接收的返回值是对象的函数调用的时候， 优先按初始化的方式接收，不要按赋值的方式接收
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

    void operator=(const Test &t)
    {
        std::cout << " operator=(const Test &t)!\n";
        m_a = t.m_a;
    }

    int get_data() const { return m_a; }
};

Test GetObject(Test t) // 不能返回局部/临时变量的引用 或 指针
{
    int val = t.get_data();
    Test tmp(val); // 4.构造
    return tmp;    // 5. 先在main栈帧上拷贝构造一个临时对象  6.t析构 7.tmp析构
}

Test GetObjectWithRef(Test &t) // 引用传值
{
    int val = t.get_data();
    return Test(val); // 返回临时对象
}

Test &GetObjectRef(Test t)
{
    int val = t.get_data();
    static Test tmp(val);
    return tmp;
}

Test *GetObjectPtr(Test t)
{
    int val = t.get_data();
    static Test tmp(val); // 整个程序运行结束后才会销毁
    return &tmp;
}

int main()
{
    Test t1;                        // 1.构造
    Test t2 = GetObjectWithRef(t1); // 用临时对象拷贝构造同类型的新对象t2的时候， 可以直接触发构造t2

    // t2 = GetObjectWithRef(t1);
    return 0;
}