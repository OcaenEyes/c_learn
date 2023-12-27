/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 07:53:06
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 07:55:23
 * @FilePath: /c++/knowledge/c++实现数据库连接池/src/connection_pool.cpp
 * @Description: 注释信息
 */
#include "connection_pool.h"

ConnectionPool::ConnectionPool()
{
}

ConnectionPool::~ConnectionPool()
{
}

// 线程安全的懒汉单例函数接口
ConnectionPool *ConnectionPool::getInstance()
{
    // 第一次运行的时候才会初始化
    static ConnectionPool connPool; // 静态变量， 由编译自动进行lock和unlock
    return &connPool;
}
