/*
 * @Author: OCEAN.GZY
 * @Date: 2022-10-06 14:54:07
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-10-06 15:00:46
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/内联成员函数/user.h
 * @Description: 注释信息
 */
#ifndef CUSER_H
#define CUSER_H
#include "iostream"

class user
{
private:
    /* data */
    char m_username[128];
    char m_password[128];

public:
    user(/* args */);
    ~user();
    inline char *get_username() const; // 定义一个内联成员函数， 后面加const表示只读
    char *get_password();
};

user::user(/* args */)
{
}

user::~user()
{
}

#endif