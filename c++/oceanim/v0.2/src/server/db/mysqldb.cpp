/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 13:12:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 14:18:03
 * @FilePath: /c++/oceanim/v0.2/src/server/db/mysqldb.cpp
 * @Description: 注释信息
 */
#include "db/mysqldb.h"

// 初始化数据库
MySQLDB::MySQLDB()
{
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQLDB::~MySQLDB()
{
    if (_conn != nullptr)
    {
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySQLDB::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(), passwd.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        // c和c++代码默认的字符是ASCII， 如果不设置，则从mysql取到的数据会变成乱码
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "mysql数据库连接成功～";
    }
    else
    {
        LOG_INFO << "mysql数据库连接失败！";
    }
    return p;
}

// 更新操作
bool MySQLDB::update(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败!";
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES *MySQLDB::query(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}
MYSQL *MySQLDB::getConnection()
{
    return _conn;
}
