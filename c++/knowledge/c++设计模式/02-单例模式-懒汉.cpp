

#include <iostream>

class Singleton
{
public:
    static Singleton *getInstance()
    {
        // 是线程安全的， 函数静态局部变量的初始化， 在汇编指令上已经自动增加了线程互斥指令了
        static Singleton instance; // 函数静态局部变量, 程序第一次运行的时候初始化，
        return &instance;
    }

private:
    // 限制构造函数，  构造函数私有化
    Singleton() {}
    // 限制析构函数，  析构函数私有化
    ~Singleton() {}
    // 限制拷贝
    Singleton(const Singleton &) = delete;
    // 限制赋值操作
    Singleton &operator=(const Singleton &) = delete;
};

int main()
{

    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
    std::cout << p3 << "\n";

    return 0;
}