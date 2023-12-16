/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-16 02:25:29
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-16 04:34:54
 * @FilePath: /c++/oceanim/v0.2/include/model/groupchat_model.h
 * @Description: groupchat表的业务操作类
 */
#include "model/groupchat.hpp"

class GroupChatModel
{
private:
    /* data */
public:
    GroupChatModel(/* args */);
    ~GroupChatModel();

    // 插入数据
    void insert(GroupChat &groupchat);

    // 查询数据
    std::vector<GroupChat> queryByToUserId(int toid);

    // 更新状态
    void update(int );
};
