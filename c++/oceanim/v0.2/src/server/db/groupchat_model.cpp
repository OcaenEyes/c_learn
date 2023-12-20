/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-18 07:38:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 02:53:56
 * @FilePath: /c++/oceanim/v0.2/src/server/db/groupchat_model.cpp
 * @Description: 注释信息
 */
#include "model/groupchat_model.h"
#include "db/mysqldb.h"

GroupChatModel::GroupChatModel()
{
}

GroupChatModel::~GroupChatModel()
{
}

void GroupChatModel::insert(GroupChat &groupchat)
{
    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into groupchat(fromid,groupid,fromname,msgtype,message,sendtime) values(%d,%d,'%s','%s','%s','%s')", groupchat.getFromId(), groupchat.getGroupId(), groupchat.getFromName().c_str(), groupchat.getMsgType().c_str(), groupchat.getMessage().c_str(), groupchat.getSendTime().c_str());

    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        if (_mysqldb.update(sql))
        {
            groupchat.setId(mysql_insert_id(_mysqldb.getConnection()));
        }
    }
}

std::vector<GroupChat> GroupChatModel::queryByToUserId(int toid)
{

    std::vector<GroupChat> groupchats_vec;
    MySQLDB _mysqldb;

    // 组装sql
    char sql[1024] = {0};
    sprintf(sql, "select a.userid as toid,b.fromid,b.groupid,b.fromname,b.msgtype,b.message,b.sendtime from groupuser a inner join groupchat b on a.groupid=b.groupid where a.userid=%d", toid);

    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            GroupChat temp;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                temp.setToId(atoi(row[0]));
                temp.setFromId(atoi(row[1]));
                temp.setGroupId(atoi(row[2]));
                temp.setFromName(row[3]);
                temp.setMsgType(row[4]);
                temp.setMessage(row[5]);
                temp.setSendTime(row[6]);
                groupchats_vec.push_back(temp);
            }
        }
    }

    return groupchats_vec;
}

void GroupChatModel::update(int)
{
}
