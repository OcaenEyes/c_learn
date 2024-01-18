/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 11:55:20
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 13:18:51
 * @FilePath: /c++/knowledge/c++设计模式/01-单例模式.cpp
 * @Description: 注释信息
 */

#include <iostream>
#include <mutex>

// 单例模式， 一个类不管创建多少次对象， 永远只能得到该类型 一个对象的实例

// 常用于： 日志模块、数据库模块

// 单例模式：
// 1. 懒汉模式：唯一的实例对象，直到第一次获取他的时候 才产生
// 2. 饿汉模式： 还没有获取实例对象， 实例对象就已经产生了，一定是线程安全的

std::mutex mtx; // 结合懒汉模式实现线程安全

class Singleton
{
public:
    // 3. 获取类的唯一实例对象的接口方法
    static Singleton *getInstance()
    {
        return instance; // 饿汉模式 ， 线程安全

        if (instance_ == nullptr) // 懒汉模式  + 锁+双重判断
        {
            std::lock_guard<std::mutex> guard(mtx);
            if (instance_ == nullptr)
            {
                instance_ = new Singleton();
            }
        }
        return instance_;
    }

private:
    // 1.限制构造函数，  构造函数私有化
    Singleton() {}
    // 限制析构函数，  析构函数私有化
    ~Singleton() {}
    // 限制拷贝
    Singleton(const Singleton &) = delete;
    // 限制赋值操作
    Singleton &operator=(const Singleton &) = delete;

    // 2.定义一个唯一的类实例对象
    static Singleton *instance; // 静态成员变量，需要在类外初始化， 饿汉模式

    /***
     * volatile提醒编译器它后面所定义的变量随时都有可能改变，因此编译后的程序每次需要存储或读取这个变量的时候，告诉编译器对该变量不做优化，都会直接从变量内存地址中读取数据，从而可以提供对特殊地址的稳定访问。
        如果没有volatile关键字，则编译器可能优化读取和存储，可能暂时使用寄存器中的值，如果这个变量由别的程序更新了的话，将出现不一致的现象。（简洁的说就是：volatile关键词影响编译器编译的结果，用volatile声明的变量表示该变量随时可能发生变化，与该变量有关的运算，不要进行编译优化，以免出错）
    */
    static Singleton *volatile instance_; // 懒汉模式
};

Singleton Singleton::*instance; // 静态成员变量，需要在类外初始化 ，饿汉模式

Singleton Singleton::*volatile instance_ = nullptr; // 懒汉模式
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