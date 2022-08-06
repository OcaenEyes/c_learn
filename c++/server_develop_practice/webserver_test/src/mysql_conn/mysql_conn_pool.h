/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-05 23:26:03
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-06 15:01:28
 * @FilePath: /c++/server_develop_practice/webserver_test/src/mysql_conn/mysql_conn_pool.h
 * @Description: 注释信息
 */
#ifndef MYSQL_CONN_POOL_H
#define MYSQL_CONN_POOL_H

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <cstring>
#include <iostream>
#include "locker.h"
#include "log.h"

class mysql_conn_pool
{
private:
    mysql_conn_pool(/* args */);
    ~mysql_conn_pool();

    int m_MaxConn;  //最大连接数
    int m_CurConn;  //当前已使用的连接数
    int m_FreeConn; //当前空闲的连接数
    locker lock;
    std::list<MYSQL *> connList;
    sem reserve;

public:
    std::string m_url;
    std::string m_Port;         //数据库端口号
    std::string m_User;         //登陆数据库用户名
    std::string m_PassWord;     //登陆数据库密码
    std::string m_DatabaseName; //使用数据库名
    int m_close_log;            //日志开关
public:
    MYSQL *GetConnection();              // 获取数据库连接
    bool ReleaseConnection(MYSQL *conn); // 释放连接
    int GetFreeConn();                   //获取连接
    void DestroyPool();                  //销毁所有连接

    // 单例模式
    static mysql_conn_pool *GetInstance();
    void init(std::string url,
              std::string User,
              std::string PassWord,
              std::string DataBaseName,
              int Port,
              int MaxConn,
              int close_log);
};

class connectionRAII
{
private:
    MYSQL *conRAII;
    mysql_conn_pool *poolRAII;

public:
    connectionRAII(MYSQL **con, mysql_conn_pool *conPool);
    ~connectionRAII();
};

#endif