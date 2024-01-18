/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 11:55:20
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 12:01:40
 * @FilePath: /c++/knowledge/c++设计模式/01-单例模式.cpp
 * @Description: 注释信息
 */

#include <iostream>

// 单例模式， 一个类不管创建多少次对象， 永远只能得到该类型 一个对象的实例

// 常用于： 日志模块、数据库模块

class Singleton
{
public:
    // 3. 获取类的唯一实例对象的接口方法
    static Singleton *getInstance()
    {
        return &instance;
    }

private:
    // 1.限制构造函数，  构造函数私有化
    Singleton() {}
    // 限制析构函数，  析构函数私有化
    ~Singleton() {}

    // 2.定义一个唯一的类实例对象
    static Singleton instance; // 静态成员变量，需要在类外初始化
};

Singleton Singleton::instance; // 静态成员变量，需要在类外初始化

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