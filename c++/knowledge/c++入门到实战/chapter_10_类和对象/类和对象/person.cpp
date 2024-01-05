/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 10:07:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 10:18:06
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/person.cpp
 * @Description: 注释信息
 */
#include "person.h"
person::person(/* args */)
{
}

person::~person()
{
}

short person::getAge()
{
    return m_age;
}

int person::setAge(short age)
{
    m_age = age;
    return 0;
}

int person::getIndex()
{
    return m_index;
};
int person::setIndex(int index)
{
    m_index = index;
    return 0;
};
char *person::getName()
{
    return m_name;
};
int person::setName(char name[25])
{
    strcpy(m_name, name);
    return 0;
};
double person::getSalary()
{
    return m_salary;
};
int person::setSalary(double salary)
{
    m_salary = salary;
    return 0;
};