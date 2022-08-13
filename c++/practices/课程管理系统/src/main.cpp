/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 23:06:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 13:30:52
 * @FilePath: /c++/practices/课程管理系统/src/main.cpp
 * @Description: 注释信息
 */
#include "CmdManager.h"

int main(int argc, char *argv[])
{

    // 输入的命令
    int cmd;

    // 创建命令管理对象
    CmdManager cmdManager;
    cmdManager.Init();

    // 打印帮助信息
    cmdManager.PrintAllHelp();

    std::cout << "输入新的命令:" << std::endl;

    // 进入主循环并处理输入信息
    while (std::cin >> cmd)
    {
        /* code */
        if (std::cin.good())
        {
            /* code */
            bool exitCode = cmdManager.HandleCmd((CourseCmd)cmd);
            if (!exitCode)
            {
                /* code */
                return 0;
            }
        }
        std::cout << "***********************************" << std::endl;
        std::cout << "新的命令" << std::endl;

        // 清理输入流， 避免刚才流中的字符影响后续输入
        std::cin.clear();
        std::cin.ignore();
    }

    return 0;
}