/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 22:54:50
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 14:06:56
 * @FilePath: /c++/practices/课程管理系统/src/CmdManager.h
 * @Description: 注释信息
 */
#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include "Cmd.h"
#include "CourseManager.h"
#include <map>
#include <istream>

/**
 * 命令管理类
 *
 */
class CmdManager
{
private:
    /* data */
    // 课程管理对象
    CourseManager manager;

    // 使用map 存储命令集帮助信息
    std::map<CourseCmd, std::string> cmdMap;

public:
    CmdManager(/* args */);
    ~CmdManager();

    // 初始化函数，初始化支持的命令及课程信息
    void Init();

    // 打印帮助信息
    void PrintAllHelp() const;

    // 根据命令查询帮助信息
    void PrintCmdHelp(const CourseCmd cmd) const;

    // 处理命令操作
    bool HandleCmd(const CourseCmd cmd);

    // 返回课程管理对象
    CourseManager &GetCourseManager() { return manager; };
};

#endif