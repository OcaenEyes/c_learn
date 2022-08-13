/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-13 13:49:53
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 19:22:52
 * @FilePath: /c++/practices/课程管理系统/src/CmdManager.cpp
 * @Description: 注释信息
 */
#include "CmdManager.h"

void CmdManager::Init()
{
    // 初始化课程列表
    manager.AddCourse("Linux");
    manager.AddCourse("NodeJS");
    manager.AddCourse("C++");
    manager.AddCourse("Python");
    manager.AddCourse("Spark");
    manager.AddCourse("Hadoop");
    manager.AddCourse("Ruby");
    manager.AddCourse("Java");

    // 初始化命令列表
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_PrintHelp, "Help"));
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_PrintCourse, "Course List"));
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_PrintCourseNum, "Course Number"));
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_PrintLongName, "Longest Course Name"));
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_RemoveLastCourse, "Remove Last Course"));
    cmdMap.insert(std::pair<CourseCmd, std::string>(Cmd_Exit, "Exit"));
}

// 打印帮助信息
void CmdManager::PrintAllHelp() const
{
    std::cout << "命令列表" << std::endl;

    for (auto iter = cmdMap.begin(); iter != cmdMap.end(); iter++)
    {
        /* code */
        std::cout << iter->first << ":" << iter->second << std::endl;
    }
}

// 根据命令打印帮助信息
void CmdManager::PrintCmdHelp(const CourseCmd cmd) const
{
    auto iter = cmdMap.find(cmd);
    if (iter != cmdMap.end())
    {
        /* code */
        std::cout << iter->first << ":" << iter->second << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

// 处理命令操作， 如果返回false则表示退出程序，其他情况返回true
bool CmdManager::HandleCmd(const CourseCmd cmd)
{
    auto iter = cmdMap.find(cmd);

    if (iter == cmdMap.end())
    {
        /* code */
        std::cout << "not found" << std::endl;
        return true;
    }

    switch (cmd)
    {
    case Cmd_PrintHelp:
        /* code */
        PrintAllHelp();
        break;
    case Cmd_PrintCourse:
        manager.PrintAllCourse();
        break;
    case Cmd_PrintCourseNum:
        std::cout << manager.GetCourseNum() << std::endl;
        break;
    case Cmd_PrintLongName:
        manager.PrintLongNameCourse();
        break;
    case Cmd_RemoveLastCourse:
        manager.RemoveLast();
        break;
    case Cmd_Exit:
        return false;
    default:
        break;
    }

    return true;
}