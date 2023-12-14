/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:33:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 08:46:36
 * @FilePath: /c++/oceanim/v0.2/include/model/friend.hpp
 * @Description: 好友ORM类
 */
#pragma once
class Friend
{
private:
    int userid;
    int friendid;

public:
    Friend(int userid = -1, int friendid = -1)
    {
        this->userid = userid;
        this->friendid = friendid;
    }
    ~Friend() {}

    void setUserId(int userid) { this->userid = userid; }
    void setFriendId(int friendid) { this->friendid = friendid; }

    int getUserId() { return userid; }
    int getFriendId() { return friendid; }
};
