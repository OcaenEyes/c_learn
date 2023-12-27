/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 03:13:50
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 07:47:37
 * @FilePath: /c++/knowledge/c++实现数据库连接池/src/main.cpp
 * @Description: 注释信息
 */
#include "db/mysql_connection.hpp"

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

    return 0;
}