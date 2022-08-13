/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 22:48:34
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 13:23:02
 * @FilePath: /c++/practices/课程管理系统/src/Course.h
 * @Description: 注释信息
 */

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <istream>
#include <ostream>

/**
 * 课程类:存储和处理课程信息
 *
 */
class Course
{

    // 友元函数：读取输入创建新的课程
    friend void read(std::istream &inpuStream, Course &course);

protected:
    /* data */
    int id;
    static int currentId;

    std::string name;

public:
    // 无参数构造函数
    Course(/* args */);
    ~Course();

    // 课程类构造函数：根据课程名称创建课程对象
    Course(const std::string &cName) : Course()
    {
        name = cName;
    };
    // 课程类拷贝构造函数
    Course(const Course &course);

    // 打印课程信息
    virtual void PrintInfo() const;

    // 返回课程名称
    inline std::string GetName() const { return name; };

    // 设置课程名称
    inline void SetName(const std::string &newName) { name = newName; };

    // 返回课程id
    inline const int GetId() const { return id; };

    // 操作符 << 重载函数， 当cout<<输出课程信息时使用
    friend std::ostream &operator<<(std::ostream &out, const Course &course);
};

// 课程分为基础课，项目课，评估课三种不同类型
// 基础课为基础Course类，  而项目课和 评估课均为继承自基础课
// 项目课：额外增加标签

class ProjectCourse : public Course
{
private:
    std::string tag;

public:
    // 设置标签
    inline void SetTag(const std::string &newTag) { tag = newTag; };

    // 返回标签
    inline std::string GetTag() const { return tag; };

    // 打印课程信息
    virtual void PrintInfo() const override;
};

// 评估课： 比基础课增加时间限制
class JudgeCourse : public Course
{

public:
    // 设置限时
    inline void SetTime(int newTime) { time = newTime; };

    // 返回限时
    inline int GetTime() { return time; };

    // 打印课程信息
    virtual void PrintInfo() const override;

private:
    int time;
};

#endif
