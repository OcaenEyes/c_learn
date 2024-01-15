/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:35:37
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 03:00:47
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/ocean_mprpc_application.h
 * @Description: 注释信息
 */
#pragma once

#include "ocean_mprpc_config.h"

// ocean_mprpc框架的基础类 --->单例模式； 负责框架的一些初始化
class OCEANMprpcApplication
{

public:
    static void Init(int argc, char **argv);

    static OCEANMprpcApplication &GetInstance();
    static OCEANMprpcConfig& GetConfig();

private:
    OCEANMprpcApplication(/* args */);
    ~OCEANMprpcApplication();

    // 禁用拷贝构造
    OCEANMprpcApplication(const OCEANMprpcApplication &) = delete;
    OCEANMprpcApplication(OCEANMprpcApplication &&) = delete;
    // 禁用赋值操作
    OCEANMprpcApplication &operator=(const OCEANMprpcApplication &) = delete;

    static OCEANMprpcConfig m_config;
};
