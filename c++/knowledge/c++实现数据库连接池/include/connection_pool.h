/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 14:49:08
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-28 07:35:11
 * @FilePath: /c++/knowledge/c++实现数据库连接池/include/connection_pool.h
 * @Description: 注释信息
 */
#pragma once

#include <string>
#include "db/mysql_connection.hpp"
#include <queue>
#include <mutex>
#include <atomic>
#include <memory>
#include <condition_variable>

class ConnectionPool // 单例模式实现
{
public:
    // 获取连接池对象实例
    static ConnectionPool *getInstance();

    // 给外部提供接口，从连接池中获取一个可用的空闲连接 [返回外部一个智能指针，当指针不用的时候会自动析构，其实就是对资源做引用计数——当引用计数为 0 的时候，自动释放资源。  此时需要重新定义一下智能指针的释放，改为归还进入线程池]
    std::shared_ptr<MysqlConnection> getConnection();

    // 释放连接池中的连接
    void releaseConnection();

    // // 销毁连接池
    // void destroyPool();

    // ConnectionPool(const ConnectionPool&) = delete; 禁止拷贝构造

private:
    // 私有化构造函数
    ConnectionPool();
    // 私有化析构函数
    ~ConnectionPool();

    std::string _host;     // 数据库连接地址
    std::string _user;     // 数据库用户名
    std::string _password; // 数据库密码
    std::string _database; // 数据库名称

    int _port;     // 数据库端口号
    int _initSize; // 初始连接数
    int _maxConn;  // 最大连接数

    // int _maxIdle;     // 最大空闲连接数
    int _maxIdleTime; // 最大空闲连接时间

    int _connTimeout; // 数据库连接超时时间
    // int _rwTimeout;   // 数据库读写超时时间

    // int _retryCount;    // 重试次数
    // int _retryInterval; // 重试间隔

    // 存储mysql连接的队列
    std::queue<MysqlConnection *> _freeConnectionQues;

    std::mutex _freeConnectionQuesMutex; // 互斥锁，用于保护连接队列线程安全互斥锁

    std::atomic_int _connCnt; // 记录连接所创建的connection连接总数量

    std::condition_variable _cv; // 设置条件变量，用于连接生产线程和消费线程的通信

    // 从配置文件中加载配置项
    bool loadConfigFile();

    // 初始化连接池
    void initPool();

    // 运行在独立的线程中，专门负责生产新连接
    void produceConnectionTask();

    // 运行在独立的线程中，专门负责销毁空闲连接
    void scanConnectionTask();
};
