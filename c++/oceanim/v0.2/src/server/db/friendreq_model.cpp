/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 03:50:24
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 09:54:25
 * @FilePath: /c++/oceanim/v0.2/src/server/db/friendreq_model.cpp
 * @Description: friendreq表的操作类实现
 */
#include "model/friendreq_model.h"
#include "db/mysqldb.h"

FriendReqModel::FriendReqModel()
{
}

FriendReqModel::~FriendReqModel()
{
}

// 插入保存
void FriendReqModel::insert(FriendReq &friendReq)
{
    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into friendreq(fromid,toid,fromname,state) values(%d,%d,'%s','%s')", friendReq.getFromId(), friendReq.getToId(), friendReq.getFromName().c_str(), friendReq.getState().c_str());

    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}

// 更新状态
void FriendReqModel::update(int userid, std::string state)
{
    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "update friendreq set state='%s' where toid=%d", state.c_str(), userid); // 收到好友请求的toid,对请求数据进行接受、拒绝、忽略

    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}

// 查询
std::vector<FriendReq> FriendReqModel::query(int userid)
{
    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "select id,fromid,toid,fromname,state from friendreq where toid=%d and state='send' or state='noop' ", userid); // 查询接收到的未处理好友请求

    MySQLDB _mysqldb;
    FriendReq temp;
    std::vector<FriendReq> vec;
    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        if (res != nullptr)
        {
            // 把userid收到所有未处理好友请求都放入vec中
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                temp.setId(atoi(row[0]));
                temp.setFromId(atoi(row[1]));
                temp.setToId(atoi(row[2]));
                temp.setFromName(row[3]);
                temp.setState(row[4]);
                vec.push_back(temp);
            }
            mysql_free_result(res); // 释放res资源
        }
    }
    return vec;
}
