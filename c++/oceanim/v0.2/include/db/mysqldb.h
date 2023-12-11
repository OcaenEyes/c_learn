#pragma once

#include <mysql/mysql.h>
#include <string>
#include "muduo/base/Logging.h"

// 数据库配置信息
static std::string server = "127.0.0.1";
static std::string user = "root";
static std::string passwd = "123456";
static std::string dbname = "oceanim";

class MySQLDB
{
private:
    MYSQL *_conn;

public:
    // 初始化数据库连接
    MySQLDB(/* args */);
    // 释放数据库连接
    ~MySQLDB();
    // 连接数据库
    bool connect();
    // 更新操作
    bool update(std::string sql);
    // 查询操作
    MYSQL_RES *query(std::string sql);
    //获取连接
    MYSQL* getConnection();
};
