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
    std::vector<GroupUser> getGroupUsers() { return groupusers; }
};
