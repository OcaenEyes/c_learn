/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 23:08:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 09:39:04
 * @FilePath: /c++/practices/课程管理系统/src/Course.cpp
 * @Description: 注释信息
 */

#include "Course.h"

// 初始化静态成员， 默认第一个课程id为1
int Course::currentId = 1;

Course::Course(/* args */)
{
    // 将currentId当前值 复制给id, 再将currentId自增
    id = currentId++;

    // 默认课程名称为空字符串
    name = "";
}

std::ostream &operator<<(std::ostream &os, const Course &course)
{
    os << "Course" << course.id << ":" << course.name;
    return os;
}

Course::~Course()
{
}