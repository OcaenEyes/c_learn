/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 03:50:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 07:17:40
 * @FilePath: /c++/oceanim/v0.2/src/server/db/friend_model.cpp
 * @Description: friend表的操作类实现
 */
#include "model/friend_model.h"
#include "db/mysqldb.h"

FriendModel::FriendModel()
{
}

FriendModel::~FriendModel()
{
}

void FriendModel::insert(Friend &f)
{
    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into friend(userid,friendid) values(%d,%d)", f.getUserId(), f.getFriendId());

    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}

std::vector<int> FriendModel::query(int userid)
{

    MySQLDB _mysqldb;
    std::vector<int> vec;

    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "select friendid from friend where userid = %d", userid);

    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            vec.push_back(atoi(row[0]));
        }
        sprintf(sql, "select userid from friend where friendid = %d", userid);
        res = _mysqldb.query(sql);
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            vec.push_back(atoi(row[0]));
        }

        mysql_free_result(res);
    }
    return vec;
}
