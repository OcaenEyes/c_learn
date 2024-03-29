#pragma once

#include <unordered_map>
#include <string>

/// @brief  框架读取配置文件类
class OCEANMprpcConfig
{
private:
    std::unordered_map<std::string, std::string> m_config_map;

public:
    OCEANMprpcConfig(/* args */);
    ~OCEANMprpcConfig();

    // 负责解析加载配置文件
    void LoadConfigFile(const char *config_file);
    // 查询配置项信息， 即为key对应的value
    std::string Load(std::string key);

    // 移除字符串前后的空格
    void Trim(std::string &src_buf);

    
};
