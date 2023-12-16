/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:33:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-15 14:46:09
 * @FilePath: /c++/oceanim/v0.2/include/model/friend.hpp
 * @Description: 好友ORM类
 */
#pragma once

#include "model/user.hpp"

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

    static void from_json(const nlohmann::json &js, std::vector<User> &friends)
    {
        for (auto friend_t : js["friends"])
        {
            User temp;
            User::from_json(friend_t, temp);
            friends.push_back(temp);
        }
    }
    static void to_json(nlohmann::json &js, const std::vector<User> &friends)
    {
        for (auto friend_t : friends)
        {
            nlohmann::json temp;
            User::to_json(temp, friend_t);
            js["friends"].push_back(temp);
        }
    }
};
