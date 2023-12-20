/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-15 14:53:56
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-20 02:51:10
 * @FilePath: /c++/oceanim/v0.2/include/model/groupchat.hpp
 * @Description: groupchat的orm类
 */
#pragma once

#include <string>
#include <nlohmann/json.hpp>

class GroupChat
{
private:
    int id;
    int fromid;
    int groupid;
    int toid;
    std::string fromname;
    std::string msgtype;
    // std::string readtype;
    std::string message;
    std::string sendtime;

public:
    GroupChat(
        int id = -1,
        int fromid = -1,
        int groupid = -1,
        int toid = -1,
        std::string fromname = "",
        std::string msgtype = "text",
        // std::string readtype = "noread",
        std::string message = "",
        std::string sendtime = "")
    {
        this->id = id;
        this->fromid = fromid;
        this->groupid = groupid;
        this->toid = toid;
        this->fromname = fromname;
        this->msgtype = msgtype;
        // this->readtype = readtype;
        this->message = message;
        this->sendtime = sendtime;
    }
    ~GroupChat() {}

    void setId(int id) { this->id = id; }
    void setFromId(int fromid) { this->fromid = fromid; }
    void setGroupId(int groupid) { this->groupid = groupid; }
    void setToId(int toid) { this->toid = toid; }
    void setFromName(std::string fromname) { this->fromname = fromname; }
    void setMsgType(std::string msgtype) { this->msgtype = msgtype; }
    // void setReadType(std::string readtype) { this->readtype = readtype; }
    void setMessage(std::string message) { this->message = message; }
    void setSendTime(std::string sendtime) { this->sendtime = sendtime; }

    int getId() { return id; }
    int getFromId() { return fromid; }
    int getGroupId() { return groupid; }
    int getToId() { return toid; }
    std::string getFromName() { return fromname; }
    std::string getMsgType() { return msgtype; }
    // std::string getReadType() { return readtype; }
    std::string getMessage() { return message; }
    std::string getSendTime() { return sendtime; }

    static void from_json(const nlohmann::json &js, GroupChat &groupchat)
    {
        // printf("from_json:%s", js.dump().c_str());

        js.at("id").get_to(groupchat.id);
        js.at("toid").get_to(groupchat.toid);
        groupchat.setFromId(js["fromid"].get<int>());
        groupchat.setGroupId(js["groupid"].get<int>());
        groupchat.setFromName(js["fromname"]);
        groupchat.setMsgType(js["msgtype"]);
        // // groupchat.setReadType(js["readtype"]);
        groupchat.setMessage(js["message"]);
        groupchat.setSendTime(js["sendtime"]);
    }

    static void to_json(nlohmann::json &js, const GroupChat &groupchat)
    {

        js["id"] = groupchat.id;
        js["fromid"] = groupchat.fromid;
        js["groupid"] = groupchat.groupid;
        js["toid"] = groupchat.toid;
        js["fromname"] = groupchat.fromname;
        js["msgtype"] = groupchat.msgtype;
        // js["readtype"] = groupchat.readtype;
        js["message"] = groupchat.message;
        js["sendtime"] = groupchat.sendtime;
        // printf("to_json:%s", js.dump().c_str());
    }

    static void from_json(const nlohmann::json &js, std::vector<GroupChat> &groupchats)
    {
        // printf("from_json groupchats:%s", js.dump().c_str());
        GroupChat groupchat;
        for (auto temp : js["groupchats"])
        {
            from_json(temp, groupchat);
            groupchats.push_back(groupchat);
        }
    }

    static void to_json(nlohmann::json &js, const std::vector<GroupChat> &groupchats)
    {
        nlohmann::json temp;
        for (auto groupchat_t : groupchats)
        {
            to_json(temp, groupchat_t);
            js["groupchats"].push_back(temp);
        }
        // printf("to_json groupchats:%s", js.dump().c_str());
    }
};
