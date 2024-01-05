/*
 * @Author: OCEAN.GZY
 * @Date: 2022-10-06 15:28:14
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-10-07 01:36:40
 * @FilePath: /c++/knowledge/入门到实战/chapter_11_继承和派生/继承员工类的操作员类.cpp
 * @Description: 注释信息
 */

/**
 * class 派生类名称标识符:[继承方式] 基类名标识符
 * 继承方式：public共有型 、 protected保护型 、 private私有型
 * {
 *   [访问控制修饰符:]
 *      [成员声明列表，包括类的成员变量和成员函数，新增的成员]
 * }
 *
 * 构造函数调用顺序：先调用父类构造函数， 再调用子类构造函数， 再调用子类析构函数，再调用父类析构函数
 * 
 * 如果子类定义了一个和父类一样的成员函数，则子类对象调用的时候，实际调用的时候子类的成员函数
 *
 *
 **/
#include <string.h>
#include <iostream>

class employee
{
public:
    int m_id;           // id
    char m_name[128];   //姓名
    char m_depart[128]; //部门
    employee();
    ~employee();

    void outputname()
    {
        std::cout << "员工姓名:" << m_name << std::endl; // 输出员工姓名
    }
};

employee::employee()
{
    memset(m_name, 0, 128);   // 初始化m_name
    memset(m_depart, 0, 128); // 初始化m_depart
}
employee::~employee()
{
}

class opter : public employee // 操作员类，从employee类派生而来
{
public:
    char m_password[128];
    bool login()
    {
        if (strcmp(m_name, "gzy") == 0 && strcmp(m_password, "123456") == 0)
        {
            std::cout << "登录成功！" << std::endl;
            return true;
        }
        else
        {
            std::cout << "登录失败！" << std::endl;
            return false;
        }
    }
};

int main(int argc, char *argv[])
{
    opter op;
    strcpy(op.m_name, "gzy");
    strcpy(op.m_password, "123456");
    op.login();
    op.outputname();
    return 0;
}