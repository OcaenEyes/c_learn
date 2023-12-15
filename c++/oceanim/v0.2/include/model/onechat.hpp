/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-12 11:49:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-15 12:07:25
 * @FilePath: /c++/oceanim/v0.2/include/model/onechat.hpp
 * @Description: 一对一消息
 */
#pragma once

#include <string>
#include <vector>
#include "nlohmann/json.hpp"

class OneChat
{
private:
    int id;
    int fromid;
    int toid;
    std::string msgtype;
    std::string readtype;
    std::string message;

public:
    OneChat(int id = -1,
            int fromid = -1,
            int toid = -1,
            std::string msgtype = "text",
            std::string readtype = "noread",
            std::string message = "")
    {
        this->id = id;
        this->fromid = fromid;
        this->toid = toid;
        this->msgtype = msgtype;
        this->readtype = readtype;
        this->message = message;
    }
    ~OneChat()
    {
    }

    void setId(int id) { this->id = id; }
    void setFromId(int fromid) { this->fromid = fromid; }
    void setToId(int toid) { this->toid = toid; }
    void setMsgType(std::string msgtype) { this->msgtype = msgtype; }
    void setReadType(std::string readtype) { this->readtype = readtype; }
    void setMessage(std::string message) { this->message = message; }

    int getId() { return id; }
    int getFromId() { return fromid; }
    int getToId() { return toid; }
    std::string getMsgType() { return msgtype; }
    std::string getReadType() { return readtype; }
    std::string getMessage() { return message; }

    static void from_json(const nlohmann::json &js, OneChat &onechat)
    {
        js.at("id").get_to(onechat.id);
        js.at("fromid").get_to(onechat.fromid);
        js.at("toid").get_to(onechat.toid);
        js.at("msgtype").get_to(onechat.msgtype);
        js.at("readtype").get_to(onechat.readtype);
        js.at("message").get_to(onechat.message);
    }
    static void to_json(nlohmann::json &js, const OneChat &onechat)
    {
        js = nlohmann::json{
            {"id", onechat.id},
            {"fromid", onechat.fromid},
            {"toid", onechat.toid},
            {"msgtype", onechat.msgtype},
            {"readtype", onechat.readtype},
            {"message", onechat.message},
        };
    }

    static void from_json(const nlohmann::json &js, std::vector<OneChat> &onechats)
    {
        for (auto &onechat_t : js["messages"])
        {
            OneChat temp;
            OneChat::from_json(onechat_t, temp);
            onechats.push_back(temp);
        }
    }

    static void to_json(nlohmann::json &js, const std::vector<OneChat> &onechats)
    {
        for (auto &onechat : onechats)
        {
            nlohmann::json temp;
            OneChat::to_json(temp, onechat);
            js["messages"].push_back(temp);
        }
    }
};
