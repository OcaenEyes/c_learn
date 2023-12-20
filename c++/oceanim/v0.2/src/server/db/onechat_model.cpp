/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-12 14:03:35
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 02:48:34
 * @FilePath: /c++/oceanim/v0.2/src/server/db/onechat_model.cpp
 * @Description: onechat_model的数据增改查
 */
#include "model/onechat_model.h"
#include "db/mysqldb.h"

OneChatModel::OneChatModel()
{
}

OneChatModel::~OneChatModel()
{
}

// 保存插入数据
void OneChatModel::insert(OneChat &onechat)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into onechat(fromid,toid,fromname,msgtype,readtype,message,sendtime) values(%d,%d,'%s','%s','%s','%s','%s')",
            onechat.getFromId(), onechat.getToId(), onechat.getFromName().c_str(), onechat.getMsgType().c_str(), onechat.getReadType().c_str(), onechat.getMessage().c_str(), onechat.getSendTime().c_str());
    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}

// 修改消息已读状态
void OneChatModel::update(int msgid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update onechat set readtype='read' where id=%d", msgid);
    MySQLDB _mysqldb;
    if (_mysqldb.connect())
    {
        _mysqldb.update(sql);
    }
}

// 查询未读的消息
std::vector<OneChat> OneChatModel::queryByUserId(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select id,fromid,toid,fromname,msgtype,readtype,message,sendtime from onechat where toid=%d and readtype='noread'", userid);

    MySQLDB _mysqldb;
    std::vector<OneChat> vec;
    OneChat temp;
    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);
        if (res != nullptr)
        {
            // 把userid用户的所有离线消息放入vec中返回
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                temp.setId(atoi(row[0]));
                temp.setFromId(atoi(row[1]));
                temp.setToId(atoi(row[2]));
                temp.setFromName(row[3]);
                temp.setMsgType(row[4]);
                temp.setReadType(row[5]);
                temp.setMessage(row[6]);
                temp.setSendTime(row[7]);
                vec.push_back(temp);
            }
            mysql_free_result(res);
        }
    }
    return vec;
}
