/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-15 11:40:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 08:47:23
 * @FilePath: /c++/oceanim/v0.2/include/model/group.hpp
 * @Description: allgroup的orm类
 */
#pragma once

#include <string>
#include "model/groupuser.hpp"
#include <vector>

class Group
{
private:
    int id;
    std::string groupname;
    std::string groupdesc;
    std::vector<GroupUser> groupusers;

public:
    Group(int id = -1, std::string groupname = "", std::string groupdesc = "")
    {
        this->id = id;
        this->groupname = groupname;
        this->groupdesc = groupdesc;
    }
    ~Group() {}

    void setId(int id) { this->id = id; }
    void setGroupName(std::string groupname) { this->groupname = groupname; }
    void setGroupDesc(std::string groupdesc) { this->groupdesc = groupdesc; }

    int getId() { return id; }
    std::string getGroupName() { return groupname; }
    std::string getGroupDesc() { return groupdesc; }
    std::vector<GroupUser> &getGroupUsers() { return groupusers; }

    static void from_json(const nlohmann::json &js, std::vector<Group> &groups)
    {

        for (auto i : js["groups"])
        {
            Group group;
            group.setId(i["groupid"].get<int>());
            group.setGroupName(i["groupname"]);
            group.setGroupDesc(i["groupdesc"]);
            if (i.contains("groupusers"))
            {
                for (auto j : i["groupusers"])
                {
                    GroupUser groupuser;
                    groupuser.setId(j["userid"].get<int>());
                    groupuser.setName(j["name"]);
                    groupuser.setState(j["state"]);
                    groupuser.setRole(j["grouprole"]);
                    group.getGroupUsers().push_back(groupuser);
                }
            }
            groups.push_back(group);
        }
    }

    static void to_json(nlohmann::json &js, const std::vector<Group> &groups)
    {
        for (auto i : groups)
        {
            nlohmann::json tmp;
            tmp["groupid"] = i.getId();
            tmp["groupname"] = i.getGroupName();
            tmp["groupdesc"] = i.getGroupDesc();
            for (auto j : i.getGroupUsers())
            {
                nlohmann::json temp;
                temp["userid"] = j.getId();
                temp["name"] = j.getName();
                temp["state"] = j.getState();
                temp["grouprole"] = j.getRole();
                tmp["groupusers"].push_back(temp);
            }
            js["groups"].push_back(tmp);
        }
    }
};