/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-05 23:49:01
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-06 09:49:26
 * @FilePath: /c++/server_develop_practice/webserver_test/src/mysql_conn_pool.cpp
 * @Description: 注释信息
 */

#include "mysql_conn_pool.h"

using namespace std;
mysql_conn_pool::mysql_conn_pool(/* args */)
{
    m_CurConn = 0;
    m_FreeConn = 0;
}

mysql_conn_pool *mysql_conn_pool::GetInstance()
{
    static mysql_conn_pool connPool;
    return &connPool;
}

//构造初始化
void mysql_conn_pool::init(string url, string User, string PassWord, string DBName, int Port, int MaxConn, int close_log)
{
    m_url = url;
    m_Port = Port;
    m_User = User;
    m_PassWord = PassWord;
    m_DatabaseName = DBName;
    m_close_log = close_log;

    for (int i = 0; i < MaxConn; i++)
    {
        MYSQL *con = NULL;
        con = mysql_init(con);
        if (con == NULL)
        {
            LOG_ERROR("mysql error");
            exit(1);
        }
        con = mysql_real_connect(con, url.c_str(), User.c_str(), PassWord.c_str(), DBName.c_str(), Port, NULL, 0);

        if (con == NULL)
        {
            LOG_ERROR("mysql error");
            exit(1);
        }
        connList.push_back(con);
        ++m_FreeConn;
    }
    reserve = sem(m_FreeConn);
    m_MaxConn = m_FreeConn;
}

// 当有请求时，从数据库连接池中返回一个可用连接，更新使用和空闲连接数
MYSQL *mysql_conn_pool::GetConnection()
{
    MYSQL *con = NULL;
    if (0 == connList.size())
    {
        return NULL;
    }
    reserve.wait();
    lock.lock();
    con = connList.front();
    connList.pop_front();
    --m_FreeConn;
    ++m_CurConn;
    lock.unlock();
    return con;
}

// 释放当前使用的连接
bool mysql_conn_pool::ReleaseConnection(MYSQL *con)
{
    if (NULL == con)
    {
        return false;
    }
    lock.lock();
    connList.push_back(con);
    ++m_FreeConn;
    ++m_CurConn;

    lock.unlock();
    reserve.post();

    return true;
}

// 销毁数据库连接池
void mysql_conn_pool::DestroyPool()
{
    lock.lock();
    if (connList.size() > 0)
    {
        list<MYSQL *>::iterator it;
        for (it = connList.begin(); it != connList.end(); ++it)
        {
            MYSQL *con = *it;
            mysql_close(con);
        }
        m_CurConn = 0;
        m_FreeConn = 0;
        connList.clear();
    }
    lock.unlock();
}

// 当前空闲的连接数
int mysql_conn_pool::GetFreeConn()
{
    return this->m_FreeConn;
}

mysql_conn_pool::~mysql_conn_pool()
{
    DestroyPool();
}

connRAII::connRAII(MYSQL **SQL, mysql_conn_pool *conPool)
{
    *SQL = conPool->GetConnection();
    conRAII = *SQL;
    poolRAII = conPool;
}

connRAII::~connRAII()
{
    poolRAII->ReleaseConnection(conRAII);
}