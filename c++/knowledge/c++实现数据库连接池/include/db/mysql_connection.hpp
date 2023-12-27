/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 14:44:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 03:00:24
 * @FilePath: /c++/knowledge/c++实现数据库连接池/include/db/mysql_connection.hpp
 * @Description: 注释信息
 */
#pragma once

#include <string>
#include "common/public.h"
#include <mysql/mysql.h>

class MysqlConnection
{
private:
    MYSQL *_conn;

public:
    MysqlConnection(/* args */)
    {
        // 初始化数据库连接
        _conn = mysql_init(nullptr);
    }
    ~MysqlConnection()
    {
        // 释放数据库连接资源
        if (_conn != nullptr)
        {
            mysql_close(_conn);
        }
    }

    // 连接数据库
    bool connect(std::string ip,
                 int port,
                 std::string db_name,
                 std::string username,
                 std::string password)
    {
        MYSQL *p = mysql_real_connect(_conn,
                                      ip.c_str(),
                                      username.c_str(),
                                      password.c_str(),
                                      db_name.c_str(),
                                      port, nullptr, 0);
        return p != nullptr;
    }

    // 更新操作，包括insert 、delete 、 update
    bool update(std::string sql)
    {
        if (mysql_query(_conn, sql.c_str())) // 成功返回0， 不成功返回非0值
        {
            LOG_ERROR("update mysql failed! sql:" + sql);
            return false;
        }
        return true;
    }

    // 查询数据操作
    MYSQL_RES *query(std::string sql)
    {
        if (mysql_query(_conn, sql.c_str())) // 成功返回0， 不成功返回非0值
        {
            LOG_ERROR("query mysql failed! sql:" + sql);
            return nullptr;
        }
        return mysql_use_result(_conn);
    }

    // 获取连接
    MYSQL *getConnection() { return _conn; }
};
