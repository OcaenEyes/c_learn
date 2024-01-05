/*
 * @Author: OCEAN.GZY
 * @Date: 2022-10-07 05:35:42
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-10-07 05:49:13
 * @FilePath: /c++/knowledge/入门到实战/chapter_11_继承和派生/利用虚函数实现动态绑定.cpp
 * @Description: 注释信息
 */

/**
 * 多态主要体现在虚函数上， 只要有虚函数存在，对象雷响就会在程序运行时候绑定
 * 动态绑定的实现方法： 定义一个指向基类对象的指针变量， 并使其指向同一类族中需要 调用该函数的对象， 通过该指针变量调用此虚函数
 *
 *
 **/

// 利用虚函数实现动态绑定
#include <iostream>
#include <string.h>

class employee
{
public:
    int m_id;
    char m_name[128];
    char m_depart[128];
    employee();
    ~employee();
    virtual void outputname() // 定义一个虚函数
    {
        std::cout << "员工姓名:" << m_name << std::endl;
    };
};

employee::employee()
{
    memset(m_name, 0, 128);
    memset(m_depart, 0, 128);
}
employee::~employee()
{
}

class opter : public employee
{
public:
    char m_password[128];
    void outputname() // 定义outputname 虚函数
    {
        std::cout << "操作员姓名:" << m_name << std::endl;
    }
};

int main()
{
    employee *emp = new opter(); // 定义employee类型指针，使用opter类构造
    strcpy(emp->m_name, "gzy");  // 设置m_name数据成员信息
    emp->outputname();           // 调用opter的 outputname 成员函数
    delete emp;                  //释放对象
    return 0;
}