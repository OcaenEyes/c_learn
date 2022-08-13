/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-13 10:02:33
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 12:57:55
 * @FilePath: /c++/practices/课程管理系统/src/CourseManager.cpp
 * @Description: 注释信息
 */
#include "CourseManager.h"

// 构造函数：参数为课程vector
CourseManager::CourseManager(const std::vector<Course> &course)
{
    for (auto curs = course.begin(); curs != course.end(); ++curs)
    {
        courseList.push_back(*curs);
    }
}

CourseManager::~CourseManager()
{
}

// 添加课程函数（参数为课程名称）
void CourseManager::AddCourse(const std::string &courseName)
{
    Course course(courseName);
    courseList.push_back(course);
}

// 添加课程函数（参数为课程对象）
void CourseManager::AddCourse(const Course &course)
{
    courseList.push_back(course);
}

// 删除最后一个课程
void CourseManager::RemoveLast()
{
    try
    {
        // 如果课程非空，则删除最后一门课程
        if (!courseList.empty())
        {
            courseList.pop_back();

            std::cout << "删除成功" << std::endl;
        }
        else
        {
            // 课程为空， 则抛异常，该异常被catch捕获
            throw std::runtime_error("删除失败，没有课程");
        }
    }
    catch (std::runtime_error err)
    {
        std::cout << err.what() << std::endl;
    }
}

// 删除课程:删除指定id的课程
void CourseManager::RemoveById(int id)
{
    int index = FindCourse(id);

    if (index > 0)
    {
        courseList.erase(courseList.begin() + index);
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

// 删除课程：删除指定名称的课程
void CourseManager::RemoveByName(const std::string &name)
{
    int index = FindCourse(name);

    if (index > 0)
    {
        courseList.erase(courseList.begin() + index);
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

// 打印课程列表
void CourseManager::PrintAllCourse()
{
    std::cout << "课程列表：" << std::endl;

    // 遍历courseList ，打印出所有course信息
    for (auto i = courseList.begin(); i != courseList.end(); ++i)
    {
        std::cout << *i << std::endl;
    }
}

// 打印指定课程（指定名称）
void CourseManager::PrintCourse(const std::string &name)
{
    int index = FindCourse(name);
    if (index > 0)
    {
        std::cout << courseList[index] << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

// 打印指定课程（指定id）
void CourseManager::PrintCourse(int id)
{
    int index = FindCourse(id);
    if (index > 0)
    {
        std::cout << courseList[index] << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

// 打印名称最长的课程
void CourseManager::PrintLongNameCourse()
{
    int maxLen = 0;
    // 遍历找到最长名称
    for (auto i = courseList.begin(); i != courseList.end(); ++i)
    {
        int currentLen = i->GetName().size();
        if (currentLen > maxLen)
        {
            maxLen = currentLen;
        }
    }

    // 遍历courseList 打印最长名称课程
    for (auto i = courseList.begin(); i != courseList.end(); ++i)
    {
        if (i->GetName().size() == maxLen)
        {
            std::cout << *i << std::endl;
        }
    }
}

// 根据id查找课程，返回课程在 vector中的索引
int CourseManager::FindCourse(int id)
{
    int i = 0;
    for (; i < courseList.size(); i++)
    {
        if (courseList[i].GetId() == id)
        {
            return i;
        }
    }
    return -1;
}

// 根据name查找课程，返回课程在 vector中的索引
int CourseManager::FindCourse(const std::string &name)
{
    int i = 0;
    for (; i < courseList.size(); i++)
    {
        if (courseList[i].GetName() == name)
        {
            return i;
        }
    }
    return -1;
}