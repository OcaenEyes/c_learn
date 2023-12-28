/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 14:44:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-28 07:42:52
 * @FilePath: /c++/knowledge/c++实现数据库连接池/include/db/mysql_connection.hpp
 * @Description: 注释信息
 */
#pragma once

#include <string>
#include "common/public.h"
#include <mysql/mysql.h>
#include <ctime>

class MysqlConnection
{
private:
    MYSQL *_conn;            // 表示和mysql的一条连接
    std::clock_t _startTime; // 记录进入队列的时间【从进入队列的时间开始，计算进入空闲状态后的存活时间】

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

    // 更新存活时间
    void refreshAliveTime() { _startTime = clock(); }

    // 获取存活时间
    std::time_t getAliveTime() const { return clock() - _startTime; }

private:
};
