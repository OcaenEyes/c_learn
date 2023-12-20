/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-15 01:00:13
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 08:57:46
 * @FilePath: /c++/oceanim/v0.2/src/server/db/group_model.cpp
 * @Description: allgroup、groupuser表的操作类
 */
#include "model/group_model.h"
#include "db/mysqldb.h"
#include <iostream>

GroupModel::GroupModel()
{
}

GroupModel::~GroupModel()
{
}

bool GroupModel::createGroup(Group &group)
{
    // 组装sql
    char sql[1024] = {0};
    MySQLDB _mysqldb;
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')", group.getGroupName().c_str(), group.getGroupDesc().c_str());

    if (_mysqldb.connect())
    {
        if (_mysqldb.update(sql))
        {
            group.setId(mysql_insert_id(_mysqldb.getConnection()));
            return true;
        }
    }
    return false;
}

bool GroupModel::addGroup(int userid, int groupid, std::string role)
{
    // 组装sql
    char sql[1024] = {0};
    MySQLDB _mysqldb;
    sprintf(sql, "insert into groupuser(userid,groupid,grouprole) values(%d,%d,'%s')", userid, groupid, role.c_str());
    if (_mysqldb.connect())
    {
        if (_mysqldb.update(sql))
        {
            return true;
        }
    }
    return false;
}

std::vector<Group> GroupModel::qeuryGroups(int userid)
{ // 组装sql
    char sql[1024] = {0};
    MySQLDB _mysqldb;
    std::vector<Group> groups_vec;
    // std::vector<Group> groups_vec_new;
    sprintf(sql, "select a.* from allgroup a inner join groupuser b on a.id=b.groupid  where b.userid=%d", userid);

    if (_mysqldb.connect())
    {

        MYSQL_RES *res = _mysqldb.query(sql); // 查询群组信息
        if (res != nullptr)
        {
            MYSQL_ROW row;
            Group temp;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                temp.setId(atoi(row[0]));
                temp.setGroupName(row[1]);
                temp.setGroupDesc(row[2]);
                groups_vec.push_back(temp);
            }
            mysql_free_result(res);
        }

        for (auto &i : groups_vec)
        {
            // std::cout << "查询群成员中\n";
            // std::cout << "查询到群XX" << i.getGroupName() << "中\n";
            sprintf(sql, "select a.id,a.name,a.state,b.grouprole from user a inner join groupuser b on b.userid = a.id where b.groupid=%d", i.getId());
            MYSQL_RES *res = _mysqldb.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    GroupUser tmp;
                    tmp.setId(atoi(row[0]));
                    tmp.setName(row[1]);
                    tmp.setState(row[2]);
                    tmp.setRole(row[3]);
                    i.getGroupUsers().push_back(tmp);
                    // groups_vec_new.push_back(i);
                }
                mysql_free_result(res);
            }

            // std::cout << "sql查询的结果--->群名字:" << i.getGroupName() << "群成员数量:" << i.getGroupUsers().size() << "\n";
        }
    }
    return groups_vec;
}

std::vector<int> GroupModel::qeuryGroupUsers(int userid, int groupid)
{
    // 组装sql
    char sql[1024] = {0};
    MySQLDB _mysqldb;
    std::vector<int> userids_vec;
    sprintf(sql, "select userid from groupuser where groupid=%d and userid != %d", groupid, userid);

    if (_mysqldb.connect())
    {
        MYSQL_RES *res = _mysqldb.query(sql);

        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                userids_vec.push_back(atoi(row[0]));
            }
            mysql_free_result(res);
        }
    }
    return userids_vec;
}
