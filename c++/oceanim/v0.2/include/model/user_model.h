/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 14:02:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 14:19:21
 * @FilePath: /c++/oceanim/v0.2/include/model/user_model.h
 * @Description: User表的操作类
 */
#pragma once

#include "model/user.hpp"

class UserModel
{
private:
    /* data */
public:
    UserModel(/* args */);
    ~UserModel();
    // 插入数据
    bool insert(User &user);
};
