/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 02:41:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 02:46:40
 * @FilePath: /c++/oceanim/v0.2/include/common/common.h
 * @Description: 注释信息
 */
#pragma once

enum EnMsgCategory
{
    ERR_REQ = 0,    // 请求不合法
    LOGIN_MSG,      // 登录
    REGIST_MSG,     // 注册
    ONE_CHAT_MSG,   // 一对一聊天
    GROUP_CHAT_MSG, // 群聊天
    FRIEND_REQ_RES, // 发送好友请求/处理好友请求/添加成功好友
    LOGIN_MSG_ACK,  // 登录响应消息
    REGIST_MSG_ACK  // 注册响应消息
};