/*
 * @Author: OCEAN.GZY
 * @Date: 2022-10-06 13:56:17
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-10-06 14:45:38
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/test.cpp
 * @Description: 注释信息
 */
#include "person.h"
#include <iostream>

void test_person()
{
    int iResult = -1;
    person p;
    iResult = p.setAge(25);
    if (iResult >= 0)
    {
        std::cout << "m_age is:" << p.getAge() << std::endl;
    }

    iResult = p.setIndex(0);
    if (iResult >= 0)
    {
        std::cout << "m_index is:" << p.getIndex() << std::endl;
    }

    char buftmp[] = "gzy";
    iResult = p.setName(buftmp);
    if (iResult >= 0)
    {
        std::cout << "m_cname is:" << p.getName() << std::endl;
    }

    iResult = p.setSalary(1700.25);
    if (iResult >= 0)
    {
        std::cout << "m_salary is:" << p.getSalary() << std::endl;
    }

}

int main()
{
    test_person();
    return 0;
}
