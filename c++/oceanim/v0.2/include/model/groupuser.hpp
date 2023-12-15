#pragma once

#include "model/user.hpp"
class GroupUser : public User
{
private:
    std::string role;

public:
    GroupUser(/* args */) {}
    ~GroupUser() {}

    void setRole(std::string role) { this->role = role; }
    std::string getRole() { return role; }
};
