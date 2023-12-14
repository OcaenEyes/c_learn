#pragma once

#include <string>

class GroupChat
{
private:
    int id;
    int fromid;
    int groupid;
    std::string msgtype;
    std::string message;

public:
    GroupChat(
        int id = -1,
        int fromid = -1,
        int groupid = -1,
        std::string msgtype = "text",
        std::string message = "")
    {
        this->id = id;
        this->fromid = fromid;
        this->groupid = groupid;
        this->msgtype = msgtype;
        this->message = message;
    }
    ~GroupChat() {}

    void setId(int id) { this->id = id; }
    void setFromId(int fromid) { this->fromid = fromid; }
    void setGroupId(int toid) { this->groupid = groupid; }
    void setMsgType(std::string msgtype) { this->msgtype = msgtype; }
    void setMessage(std::string message) { this->message = message; }

    int getId() { return id; }
    int getFromId() { return fromid; }
    int getGroupId() { return groupid; }
    std::string getMsgType() { return msgtype; }
    std::string getMessage() { return message; }
};
