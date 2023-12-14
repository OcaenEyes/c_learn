/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 06:42:39
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 06:42:39
 * @FilePath: /c++/oceanim/v0.2/include/model/friendreq_model.h
 * @Description: friendreq表的操作类
 */

#pragma once

#include "model/friendreq.hpp"
#include <vector>

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
    std::vector<FriendReq> query(int userid);
};
