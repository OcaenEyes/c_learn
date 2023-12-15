/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:41:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-15 05:56:32
 * @FilePath: /c++/oceanim/v0.2/include/common/common.h
 * @Description: 注释信息
 */
#pragma once

enum EnMsgCategory
{
    ERR_REQ = 0,          // 请求不合法
    LOGIN_MSG = 1,        // 登录
    REGIST_MSG = 2,       // 注册
    ONE_CHAT_MSG = 3,     // 一对一聊天
    GROUP_CHAT_MSG = 4,   // 群聊天
    FRIEND_REQ_RES = 5,   // 发送好友请求/处理好友请求/添加成功好友
    CREATE_GROUP_MSG = 6, // 创建群
    ADD_GROUP_MSG = 7,    // 加入群
    LOGIN_MSG_ACK,        // 登录响应消息
    REGIST_MSG_ACK,       // 注册响应消息
    CREATE_GROUP_MSG_ACK, // 创建群响应消息
    ADD_GROUP_MSG_ACK     // 加群响应消息
};

enum EnOpFriendReqType
{
    SEND = 0,   // 发送请求
    ACCEPT = 1, // 接受请求
    REFUSE = 2, // 拒绝请求
    IGNORE = 3, // 忽略请求
};