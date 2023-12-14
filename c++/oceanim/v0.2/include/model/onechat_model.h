/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-12 13:55:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-12 14:02:49
 * @FilePath: /c++/oceanim/v0.2/include/model/onechat_model.h
 * @Description: 注释信息
 */
#pragma once
#include "model/onechat.hpp"
#include <vector>

class OneChatModel
{
private:
    /* data */
public:
    OneChatModel(/* args */);
    ~OneChatModel();

    // 存储用户的消息
    void insert(OneChat &onechat);

    // 修改消息的接收状态
    void update(int msgid);

    // 查询用户的未读消息
    std::vector<OneChat> queryByUserId(int userid);
};
