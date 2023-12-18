/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 14:05:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-18 07:28:11
 * @FilePath: /c++/oceanim/v0.2/src/server/db/user_model.cpp
 * @Description: 注释信息
 */
#include "model/user_model.h"
#include "db/mysqldb.h"
#include <iostream>

UserModel::UserModel()
{
}

UserModel::~UserModel()
{
}

// User表增加的方法
bool UserModel::insert(User &user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,password,state,registime) values('%s','%s','%s','%s')", user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str(), user.getRegistime().c_str());
    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        if (_mysqldb.update(sql))
        {
            // 获取插入成功的用户数据生成的主键ID
            user.setId(mysql_insert_id(_mysqldb.getConnection()));
            return true;
        }
    }
    return false;
}

// 根据ID查询用户信息
User UserModel::queryById(int id)
{

    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id=%d", id);
    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                user.setRegistime(row[4]);
                mysql_free_result(res);
                return user;
            }
        }
    }

    return User();
}

// 更新用户信息
bool UserModel::update(User &user)
{
    // 组装sql语句
    char sql[1024];
    sprintf(sql, "update user set state='%s' where id =%d", user.getState().c_str(), user.getId());

    MySQLDB _mysqldb;

    if (_mysqldb.connect())
    {
        if (_mysqldb.update(sql))
        {
            return true;
        }
    }
    return false;
}

// 重置用户状态
void UserModel::resetState()
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state='offline' where state='online'");

    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}