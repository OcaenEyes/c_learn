/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 10:03:05
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 10:23:49
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/person.h
 * @Description: 注释信息
 */

#ifndef _PERSON_H
#define _PERSON_H
#include <cstring>
#include <iostream>
class person
{
private:
    /* data */
public:
    person(/* args */);
    ~person();
    // 成员函数
    short getAge();
    int setAge(short age);
    int getIndex();
    int setIndex(int index);
    char *getName();
    int setName(char name[25]);
    double getSalary();
    int setSalary(double salary);

public:
    // 数据成员
    int m_index;
    char m_name[25];
    short m_age;
    double m_salary;
};

#endif