/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 23:08:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 13:16:51
 * @FilePath: /c++/practices/课程管理系统/src/Course.cpp
 * @Description: 注释信息
 */

#include "Course.h"

// 初始化静态成员， 默认第一个课程id为1
int Course::currentId = 1;

// 课程类构造函数
Course::Course(/* args */)
{
    // 将currentId当前值 复制给id, 再将currentId自增
    id = currentId++;

    // 默认课程名称为空字符串
    name = "";
}

// 课程类拷贝构造函数
Course::Course(const Course &course)
{
    id = course.GetId();
    name = course.GetName();
}

// 打印课程信息
void Course::PrintInfo() const
{
    std::cout << "课程" << id << ":" << name << std::endl;
}

// 友元函数：读取输入创建新的课程
void read(std::istream &is, Course &item)
{
    is >> item.name;
}

// 友元函数：操作符<< 重载函数， 当std::cout<< 输出课程信息时使用
std::ostream &operator<<(std::ostream &os, const Course &course)
{
    os << "Course" << course.id << ":" << course.name;
    return os;
}

// ProjectCourse 类成员函数
// 打印课程信息
void ProjectCourse::PrintInfo() const
{
    std::cout << "项目课程:" << id << ":" << name << ":" << tag << std::endl;
}

Course::~Course()
{
}