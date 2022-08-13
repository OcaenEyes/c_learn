/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 22:51:33
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 12:16:36
 * @FilePath: /c++/practices/课程管理系统/src/CourseManager.h
 * @Description: 注释信息
 */

#ifndef COURSE_MANAGER_H
#define COURSE_MANAGER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Course.h"
/**
 * 课程管理类:用户来维护课程列表， 执行课程处理任务
 *
 */
class CourseManager
{
private:
    /* data */
    // 存储课程列表
    std::vector<Course> courseList;

    // 根据课程名称查找课程， 返回课程列表的索引值，无法找到 返回-1
    int FindCourse(const std::string &name);

    // 根据课程id查找课程， 返回课程列表中的索引值， 无法找到返回-1
    int FindCourse(int id);

public:
    CourseManager(/* args */);
    ~CourseManager();

    // 构造函数：根据课程vector 创建CourseManager
    CourseManager(const std::vector<Course> &courseVect);

    // 获取课程列表的长度
    inline int GetCourseNum()
    {
        return courseList.size();
    };

    // 添加新的课程
    void AddCourse(const Course &course);
    void AddCourse(const std::string &courseName);

    // 删除课程：删除最后一个课程
    void RemoveLast();

    // 删除课程：删除指定名称的课程
    void RemoveByName(const std::string &name);

    // 删除课程：删除指定id的课程
    void RemoveById(int id);

    // 打印课程列表信息
    void PrintAllCourse();

    // 根据课程名称打印 指定课程信息
    void PrintCourse(const std::string &name);

    // 根据课程id打印指定课程信息
    void PrintCourse(int id);

    // 打印名称最长的课程
    void PrintLongNameCourse();
};
#endif
