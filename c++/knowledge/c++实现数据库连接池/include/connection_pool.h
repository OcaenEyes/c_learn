/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 14:49:08
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 08:14:21
 * @FilePath: /c++/knowledge/c++实现数据库连接池/include/connection_pool.h
 * @Description: 注释信息
 */
#pragma once

#include <string>
#include "db/mysql_connection.hpp"
#include <queue>
#include <mutex>

class ConnectionPool // 单例模式实现
{
public:
    // 获取连接池对象实例
    static ConnectionPool *getInstance();

    // ConnectionPool(const ConnectionPool&) = delete; 禁止拷贝构造

private:
    // 私有化构造函数
    ConnectionPool();
    // 私有化析构函数
    ~ConnectionPool();

    std::string _connUrl;  // 数据库连接地址
    std::string _userName; // 数据库用户名
    std::string _password; // 数据库密码

    int _port;        // 数据库端口号
    int _connTimeout; // 数据库连接超时时间
    int _rwTimeout;   // 数据库读写超时时间
    int _maxConn;     // 最大连接数
    int _maxIdle;     // 最大空闲连接数
    int _maxIdelTime; // 最大空闲连接时间

    // 存储mysql连接的队列
    std::queue<MysqlConnection *> _freeConnections;

    std::mutex _freeConnectionsMutex; // 互斥锁，用于保护连接队列线程安全互斥锁
};
