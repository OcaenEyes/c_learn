/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 13:52:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-18 07:26:56
 * @FilePath: /c++/oceanim/v0.2/include/model/user.hpp
 * @Description: user用户的ORM类
 */
#pragma once

#include <string>
#include "nlohmann/json.hpp"

class User
{
private:
    int id;
    std::string name;
    std::string password;
    std::string state;
    std::string registime;

public:
    User(int id = -1, std::string name = "", std::string password = "", std::string state = "offline", std::string registime = "")
    {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
        this->registime = registime;
    }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setPassword(std::string password) { this->password = password; }
    void setState(std::string state) { this->state = state; }
    void setRegistime(std::string registime) { this->registime = registime; }

    int getId() { return this->id; }
    std::string getName() { return this->name; }
    std::string getPassword() { return this->password; }
    std::string getState() { return this->state; }
    std::string getRegistime() { return this->registime; }

    static void from_json(const nlohmann::json &js, User &user)
    {
        js.at("id").get_to(user.id);
        js.at("name").get_to(user.name);
        js.at("password").get_to(user.password);
        js.at("state").get_to(user.state);
        js.at("registime").get_to(user.registime);
    }
    static void to_json(nlohmann::json &js, const User &user)
    {
        js = nlohmann::json{{"id", user.id}, {"name", user.name}, {"password", user.password}, {"state", user.state}, {"registime", user.registime}};
    }
};