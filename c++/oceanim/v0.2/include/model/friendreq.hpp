/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:47:34
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 02:58:11
 * @FilePath: /c++/oceanim/v0.2/include/model/friendreq.hpp
 * @Description: 好友请求ORM类
 */
#pragma once

#include <string>

class FriendReq
{
private:
    int fromid;
    int toid;
    std::string state;

public:
    FriendReq(int fromid = -1, int toid = -1, std::string state = "send")
    {
        this->fromid = fromid;
        this->toid = toid;
        this->state = state;
    }
    ~FriendReq() {}

    void setFromId(int fromid) { this->fromid = fromid; }
    void setToId(int toid) { this->toid = toid; }
    void setState(std::string state) { this->state = state; }

    int getFromId() { return fromid; }
    int getToId() { return toid; }
    std::string getState() { return state; }
};
