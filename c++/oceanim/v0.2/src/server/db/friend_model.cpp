/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 03:50:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 14:20:10
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

std::vector<User> FriendModel::query(int userid)
{

    MySQLDB _mysqldb;
    std::vector<User> vec;

    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on a.id=b.friendid where b.userid= %d", userid);

    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        MYSQL_ROW row;
        User temp;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            temp.setId(atoi(row[0]));
            temp.setName(row[1]);
            temp.setState(row[2]);

            vec.push_back(temp); 
        }

        mysql_free_result(res);
    }
    return vec;
}
