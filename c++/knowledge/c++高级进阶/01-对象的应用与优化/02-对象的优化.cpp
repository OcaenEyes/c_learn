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
    Test t1; // 1.构造
    Test t2; // 2.构造

    // 函数调用从实参数==>到形参， 是一个初始化过程
    // 3.由t1拷贝构造形参t
    t2 = GetObject(t1); // 8.main栈帧的上临时对象赋值给t2   9.main栈帧的上临时对象析构  10.t2析构
    return 0;
}