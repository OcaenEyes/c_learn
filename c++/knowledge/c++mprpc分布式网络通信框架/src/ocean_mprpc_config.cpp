/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 14:27:51
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 06:30:07
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/ocean_mprpc_config.cpp
 * @Description: 注释信息
 */
#include "ocean_mprpc_config.h"
#include "ocean_logger.h"

#include <iostream>

OCEANMprpcConfig::OCEANMprpcConfig(/* args */)
{
}

OCEANMprpcConfig::~OCEANMprpcConfig()
{
}

void OCEANMprpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf = fopen(config_file, "r");
    if (pf == nullptr)
    {
        std::cout << config_file << "config_file is not exist! \n";
        LOG_ERROR("%s config_file is not exist!", config_file);
        exit(EXIT_FAILURE);
    }

    // 1.注释  2.正确的配置项
    while (!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        std::string src_buf(buf);

        //  去除字符串前后多余的空格
        Trim(src_buf);

        // 判断#注释
        if (src_buf[0] == '#' || src_buf.empty())
        {
            continue;
        }

        // 解析配置项
        int idx = src_buf.find('=');
        if (idx == -1)
        {
            // 配置不合法
            continue;
        }
        std::string key;
        std::string value;
        key = src_buf.substr(0, idx);
        Trim(key);

        int endidx = src_buf.find('\n', idx);
        value = src_buf.substr(idx + 1, endidx - idx - 1);
        Trim(value);

        m_config_map.insert({key, value});
    }
}

std::string OCEANMprpcConfig::Load(std::string key)
{
    auto it = m_config_map.find(key);
    if (it == m_config_map.end())
    {
        return "";
    }
    return it->second;
}

void OCEANMprpcConfig::Trim(std::string &src_buf)
{
    // 去掉字符串前面多余的空格
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    // 去掉字符串后面的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, idx + 1);
    }
}
