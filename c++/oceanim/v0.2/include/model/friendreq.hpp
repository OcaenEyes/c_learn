/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:47:34
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 03:21:04
 * @FilePath: /c++/oceanim/v0.2/include/model/friendreq.hpp
 * @Description: 好友请求ORM类
 */
#pragma once

#include <string>

class FriendReq
{
private:
    int id;
    int fromid;
    int toid;
    std::string fromname;
    std::string state;

public:
    FriendReq(int id = -1, int fromid = -1, int toid = -1, std::string fromname = "", std::string state = "noop")
    {
        this->id = id;
        this->fromid = fromid;
        this->toid = toid;
        this->fromname = fromname;
        this->state = state;
    }
    ~FriendReq() {}

    void setId(int id) { this->id = id; }
    void setFromId(int fromid) { this->fromid = fromid; }
    void setToId(int toid) { this->toid = toid; }
    void setFromName(std::string fromname) { this->fromname = fromname; }
    void setState(std::string state) { this->state = state; }

    int getId() { return id; }
    int getFromId() { return fromid; }
    int getToId() { return toid; }
    std::string getFromName() { return fromname; }
    std::string getState() { return state; }
};
