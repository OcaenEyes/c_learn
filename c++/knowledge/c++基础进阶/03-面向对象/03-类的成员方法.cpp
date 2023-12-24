/**
 * @file 03-类的成员方法.cpp
 * @author OCEANGZY
 * @brief
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * 类的成员： 成员方法/变量
 * 普通的成员方法： ====> 编译器会添加一个 this形参变量
 *  1.属于类的作用域
 *  2.调用该方法时，需要依赖一个普通对象 【常对象不能调用】
 *  3.可以任意访问对象的私有标量
 *
 *
 * static静态成员方法 =====> 不产生this形参
 *  1.属于类的作用域
 *  2.用类名作用域来调用方法
 *  3.可以任意访问对象的私有成员，仅限于不依赖对象的成员（只能调用其他的static静态成员）
 * 
 * const常成员方法====> 产生const CGoods *this
 *  1.属于类的作用域
 *  2.调用依赖一个对象，普通对象或者常对象都可以
 *  3.可以任意访问对象的私有成员。但只能读，不能写
 * 
 */

#include <string.h>
#include <iostream>
const int NAME_LEN = 20;
class CGoods // 商品的抽象类型
{

public: // 给外部提供公有的成员方法，来访问私有的属性;
    // 初始化商品信息
    CGoods(const char *name, double price, int amout);

    ~CGoods();
    // 打印商品信息
    void show(); // 普通成员方法， CGood *this

    void show() const; // 静态成员方法 const CGood *this

    // 显示所有商品种类
    static void showCount();

    // get set方法； 类体内的方法自动解析为 inline函数
    double getPrice() { return _price; }
    int getAmout() { return _amout; }
    const char *getName() { return _name; }
    void setPrice(double price) { _price = price; }
    void setAmout(int amout) { _amout = amout; }
    void setName(const char *name) { strcpy(_name, name); }

private: // 属性一版都是私有的成员变量
    char _name[NAME_LEN];
    double _price;
    int _amout;

    static int _count; // 静态成员变量，属于类的作用域，不属于对象-不依赖对象，所以不能访问私有属性, 一定要在类外定义和初始化
};

int CGoods::_count = 0;

CGoods::CGoods(const char *name, double price, int amout)
{
    strcpy(_name, name);
    _price = price;
    _amout = amout;
    _count++;
}

CGoods::~CGoods() {}

void CGoods::show() // 普通成员方法
{
    std::cout << "商品信息：" << std::endl;
    std::cout << "商品名称：" << _name << std::endl;
    std::cout << "商品价格：" << _price << std::endl;
    std::cout << "商品数量：" << _amout << std::endl;
}

void CGoods::show() const // 常成员方法
{
    std::cout << "商品信息：" << std::endl;
    std::cout << "商品名称：" << _name << std::endl;
    std::cout << "商品价格：" << _price << std::endl;
    std::cout << "商品数量：" << _amout << std::endl;
}

void CGoods::showCount()
{
    std::cout << "商品种类：" << _count << std::endl;
}

int main()
{
    CGoods good1("apple", 10.0, 10);
    CGoods good2("apple1", 10.0, 10);
    CGoods good3("apple2", 10.0, 10);
    CGoods good4("apple3", 10.0, 10);
    CGoods good5("apple4", 10.0, 10);

    const CGoods good6("apple6", 10.0, 10);
    good6.show();

    CGoods::showCount();

    return 0;
}