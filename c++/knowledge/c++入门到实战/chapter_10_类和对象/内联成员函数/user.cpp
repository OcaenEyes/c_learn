/*
 * @Author: OCEAN.GZY
 * @Date: 2022-10-06 15:01:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-10-06 15:05:30
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/内联成员函数/user.cpp
 * @Description: 注释信息
 */
#include "user.h"

char *user::get_username() const // 实现内联成员函数
{
    return (char *)user::m_username;
}
inline char *user::get_password()
{
    return (char *)user::m_password;
}

user::user(/* args */)
{
}

user::~user()
{
}