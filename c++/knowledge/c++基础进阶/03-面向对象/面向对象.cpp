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

/**
 * C++ ：OOP面向对象，
 * c++: 类 ==> 实体的抽象类型
 * 实体（属性和行为）---> ADT（abstract data type）
 * 对象            <--- （实例化）类（属性-->成员变量；  行为--->成员方法）
 *
 *
 * OOP语言的四大特征：
 *  抽象
 *  封装/隐藏： 访问限定符： public private protected
 *  继承
 *  多态
 */

const int NAME_LEN = 20;
class CGoods
{

public:  // 给外部提供公有的方法，来访问私有的属性
    
private: // 属性一版都是私有的
    char _name[NAME_LEN];
    double _price;
    int amout;
};

int main()
{
    CGoods good;
    // std::cout << good._name << "endl";  // 访问失败，不允许访问私有属性
}