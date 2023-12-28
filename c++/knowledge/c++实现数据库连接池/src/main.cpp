/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 03:13:50
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-28 08:10:21
 * @FilePath: /c++/knowledge/c++实现数据库连接池/src/main.cpp
 * @Description: 注释信息
 */
// #include "db/mysql_connection.hpp"
#include "connection_pool.h"
#include "ini_config.hpp"
#include <thread>

int testload()
{

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

    MysqlConnection conn;
    bool _state = conn.connect(_host,
                               _port,
                               _database,
                               _user,
                               _password);

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

    return 0;
}

int main()
{

    std::cout << "=====================普通数据库连接模式=================================\n";
    time_t start = clock();
    std::cout << "mysql conn mode-- time start:" << std::to_string(start) << "\n";
    for (int i = 0; i < 1000; i++)
    {
        MysqlConnection conn;
        conn.connect("172.17.0.2", 3306, "testtest", "root", "123456");
        char sql[1024] = {0};
        sprintf(sql, "insert into users(username,password,email) values('%s','%s','%s')", "gzy", "123456", "gzy@qq.com");
        conn.update(sql);
    }
    time_t end = clock();
    std::cout << "mysql conn mode-- time end:" << std::to_string(end) << "\n";
    std::cout << "mysql conn mode-- time spend:" << std::to_string(end - start) << "\n";

    std::cout << "=====================多线程连接池连接模式=================================\n";
    start = clock();
    std::cout << " connpool mode-- time start:" << std::to_string(start) << "\n";
    ConnectionPool *cp = ConnectionPool::getInstance();

    // std::thread 默认构造函数，创建一个空的 std::thread 执行对象。
    // 使用lambda表达式创建一个线程
    std::thread t1([&]()
                   {
        std::shared_ptr<MysqlConnection> p = cp->getConnection();
        for (int i = 0; i < 1000; i++)
        {
            char sql[1024] = {0};
            sprintf(sql, "insert into users(username,password,email) values('%s','%s','%s')", "gzy", "123456", "gzy@qq.com");
            p->update(sql);
        } });

    // 等待线程完成
    // 等待线程 t1 完成
    t1.join();

    end = clock();
    std::cout << "connpool mode-- time end:" << std::to_string(end) << "\n";
    std::cout << "connpool mode-- time spend:" << std::to_string(end - start) << "\n";

    return 0;
}