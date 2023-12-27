/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 03:13:50
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 15:26:56
 * @FilePath: /c++/knowledge/c++实现数据库连接池/src/main.cpp
 * @Description: 注释信息
 */
#include "db/mysql_connection.hpp"
#include "ini_config.hpp"

int main()
{
    MysqlConnection conn;
    bool _state = conn.connect("172.17.0.2",
                               3306,
                               "testtest",
                               "root",
                               "123456");

    LOG_INFO("连接状态：{"
             "state"
             ":" +
             std::to_string(_state) + "}");

    char sql[1024] = {0};
    sprintf(sql, "insert into users(username,password,email) values('%s','%s','%s')", "gzy", "123456", "gzy@qq.com");
    _state = conn.update(sql);
    LOG_INFO("数据插入状态{"
             "state"
             ":" +
             std::to_string(_state) + "}" + " sql is:" + sql);

    INIConfig ini_config;
    bool _iniState = ini_config.readConfig("./conf/config.ini");
    if (!_iniState)
    {
        LOG_ERROR("读取配置文件失败");
    }

    std::string _host = ini_config.readString("MySQL", "Host", "");
    std::string _user = ini_config.readString("MySQL", "User", "");
    std::string _password = ini_config.readString("MySQL", "Password", "");
    std::string _database = ini_config.readString("MySQL", "Database", "");
    int _port = ini_config.readInt("MySQL", "Port", 0);

    LOG_INFO("读取配置文件成功:" + _host + _user + _password + _database + std::to_string(_port));

    return 0;
}