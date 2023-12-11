/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-11 13:52:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-11 14:01:42
 * @FilePath: /c++/oceanim/v0.2/include/model/user.hpp
 * @Description: user用户的ORM类
 */
#pragma once

#include <string>

class User
{
private:
    int id;
    std::string name;
    std::string password;
    std::string state;

public:
    User(int id = -1, std::string name = "", std::string password = "", std::string state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
    }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setPassword(std::string password) { this->password = password; }
    void setState(std::string state) { this->state = state; }

    int getId() { return this->id; }
    std::string getName() { return this->name; }
    std::string getPassword() { return this->password; }
    std::string getState() { return this->state; }
};