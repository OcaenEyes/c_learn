#pragma once

#include "model/group.hpp"

class GroupModel
{
private:
    /* data */
public:
    GroupModel(/* args */);
    ~GroupModel();

    // 创建群组
    bool createGroup(Group &group);

    // 加入群组
    bool addGroup(int userid, int groupid, std::string role);

    // 根据用户ID查询所在的群组信息
    std::vector<Group> qeuryGroups(int userid);

    // 根据用户ID和群ID，查询群成员ID列表，--->用于过滤用户ID给其他成员发送消息
    std::vector<int> qeuryGroupUsers(int userid, int groupid);
};
