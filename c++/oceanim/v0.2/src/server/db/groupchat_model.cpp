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
    sprintf(sql, "insert into groupchat(fromid,groupid,msgtype,message) values(%d,%d,'%s','%s')", groupchat.getFromId(), groupchat.getGroupId(), groupchat.getMsgType().c_str(), groupchat.getMessage().c_str());

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
    sprintf(sql, "select a.userid as toid,b.fromid,b.groupid,b.msgtype,b.message from groupuser a inner join groupchat b on a.groupid=b.groupid where a.userid=%d", toid);

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
                temp.setMsgType(row[3]);
                temp.setMessage(row[4]);
                groupchats_vec.push_back(temp);
            }
        }
    }

    return groupchats_vec;
}

void GroupChatModel::update(int)
{
}
