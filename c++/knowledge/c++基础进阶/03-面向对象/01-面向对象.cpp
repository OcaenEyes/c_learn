/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-23 06:19:30
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-23 06:25:57
 * @FilePath: /c++/knowledge/c++基础进阶/03-面向对象/面向对象.cpp
 * @Description: 注释信息
 *
 */
#include <iostream>
#include <string.h>

/**
 * C++ ：OOP面向对象，
 * c++: 类 ==> 实体的抽象类型
 * 实体（属性和行为）---> ADT（abstract data type）
 * 对象            <--- （实例化）类（属性-->成员变量；  行为--->成员方法）
 *
 * 类的成员方法经过编译，所有的方法参数否会增加一个this指针， 接收调用这个该方法的对象的地址
 * 
 * 
 * OOP语言的四大特征：
 *  抽象
 *  封装/隐藏： 访问限定符： public private protected
 *  继承
 *  多态
 */

const int NAME_LEN = 20;
class CGoods  //商品的抽象类型
{

public: // 给外部提供公有的成员方法，来访问私有的属性; 
    // 初始化商品信息
    void init(const char *name, double price, int amout);

    // 打印商品信息
    void show();

//get set方法； 类体内的方法自动解析为 inline函数
    double getPrice(){return _price;}
    int getAmout(){return _amout;}
    const char *getName(){return _name;}
    void setPrice(double price){_price = price;}
    void setAmout(int amout){_amout = amout;}
    void setName(const char *name){strcpy(_name, name);}

private: // 属性一版都是私有的成员变量
    char _name[NAME_LEN];
    double _price;
    int _amout;
};

void CGoods::init(const char *name, double price, int amout){
    strcpy(_name, name);
    _price = price;
    _amout = amout;
}



void CGoods::show(){    
    std::cout << "商品信息：" << std::endl;
    std::cout << "商品名称：" << _name << std::endl;
    std::cout << "商品价格：" << _price << std::endl;
    std::cout << "商品数量：" << _amout << std::endl;
}

int main()
{
    CGoods good;
    good.init("apple", 10.0, 10);
    good.show();
    // std::cout << good._name << "endl";  // 访问失败，不允许访问私有属性
}