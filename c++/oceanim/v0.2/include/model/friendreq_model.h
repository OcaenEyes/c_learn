
#pragma once

#include "model/friendreq.hpp"

class FriendReqModel
{
private:
    /* data */
public:
    FriendReqModel(/* args */);
    ~FriendReqModel();

    // 插入保存好友请求数据
    void insert(FriendReq &friendReq);

    // 更新好友请求数据
    void update(int userid, std::string state);

    // 查询好友请求数据
    void query(int userid);
};
