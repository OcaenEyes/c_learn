/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 14:05:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 14:31:45
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
    sprintf(sql, "insert into user(name,password,state) values('%s','%s','%s')", user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());
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
