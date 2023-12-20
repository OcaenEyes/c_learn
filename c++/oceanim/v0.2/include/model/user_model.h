/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 14:02:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 02:43:22
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

    // 根据用户ID查询用户信息
    User queryById(int id);

     // 根据用户昵称查询用户信息
    User queryByName(std::string name);

    // 更新用户信息
    bool update(User &user);

    // 重置用户状态
    void resetState();
};
