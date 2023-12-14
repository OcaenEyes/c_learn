/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 03:02:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 07:12:35
 * @FilePath: /c++/oceanim/v0.2/include/model/friend_model.h
 * @Description: friend表的操作类
 */
#pragma once

#include "model/friend.hpp"
#include <vector>

class FriendModel
{
private:
    /* data */
public:
    FriendModel(/* args */);
    ~FriendModel();

    // 插入保存数据
    void insert(Friend &f);

    // 查询数据
    std::vector<int> query(int userid);
};