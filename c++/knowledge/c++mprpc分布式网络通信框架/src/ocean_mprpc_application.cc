/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:57:10
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 03:00:56
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/ocean_mprpc_application.cc
 * @Description: 注释信息
 */
#include "ocean_mprpc_application.h"

#include <iostream>
#include <unistd.h>
#include <string>

OCEANMprpcConfig OCEANMprpcApplication::m_config;

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>\n";
}

OCEANMprpcApplication::OCEANMprpcApplication()
{
}

OCEANMprpcApplication::~OCEANMprpcApplication()
{
}

void OCEANMprpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;


    /** 
     * 一、简介
            getopt() 方法是用来分析命令行参数的，该方法由 Unix 标准库提供，包含在 <unistd.h> 头文件中。

       二、定义
            int getopt(int argc, char * const argv[], const char *optstring);
            extern char *optarg;
            extern int optind, opterr, optopt;

            getopt 参数说明：
                argc：通常由 main 函数直接传入，表示参数的数量
                argv：通常也由 main 函数直接传入，表示参数的字符串变量数组
                optstring：一个包含正确的参数选项字符串，用于参数的解析。例如 “abc:”，其中 -a，-b 就表示两个普通选项，-c 表示一个必须有参数的选项，因为它后面有一个冒号
            外部变量说明：
                optarg：如果某个选项有参数，这包含当前选项的参数字符串
                optind：argv 的当前索引值
                opterr：正常运行状态下为 0。非零时表示存在无效选项或者缺少选项参数，并输出其错误信息
                optopt：当发现无效选项字符时，即 getopt() 方法返回 ? 字符，optopt 中包含的就是发现的无效选项字符
    */
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            std::cout << "invalid args! \n";
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            std::cout << "invalid args! \n";
            ShowArgsHelp();
            exit(EXIT_FAILURE);

        default:
            break;
        }
    }

    // 开始加载配置文件
    // rpcserver_ip 、 rpcserver_port 、zookeeper_ip  、 zookeeper_port
    m_config.LoadConfigFile(config_file.c_str());

    std::cout << "rpcserver_ip: " << m_config.Load("rpcserverip") << "\n";
    std::cout << "rpcserver_port: " << m_config.Load("rpcserverport") << "\n";
    std::cout << "zookeeper_ip: " << m_config.Load("zookeeperip") << "\n";
    std::cout << "zookeeper_port: " << m_config.Load("zookeeperport") << "\n";
}

OCEANMprpcApplication &OCEANMprpcApplication::GetInstance()
{
    static OCEANMprpcApplication app;
    return app;
}

OCEANMprpcConfig &OCEANMprpcApplication::GetConfig()
{
    return m_config;
}
