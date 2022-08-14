/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 10:22:07
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 10:33:24
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/object_quote.cpp
 * @Description: 注释信息
 */
#include "person.h"
using namespace std;

int main()
{
    int ires = -1;
    person p;
    ires = p.setAge(25);
    if (ires >= 0)
    {
        std::cout << "年龄是:" << p.getAge() << std::endl;
    }

    ires = p.setIndex(0);
    if (ires >= 0)
    {
        cout << "索引是:" << p.getIndex() << endl;
    }

    char bufTmp[] = "gzy";
    ires = p.setName(bufTmp);
    if (ires >= 0)
    {
        cout << "名字是:" << p.getName() << endl;
    }

    ires = p.setSalary(10.00);
    if (ires >= 0)
    {
        cout << "名字是:" << p.getSalary() << endl;
    }
}