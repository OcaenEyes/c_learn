#pragma once

#include <iosfwd>
#include <string>

class message
{
private:
    std::string m_msg;
    std::ostream &printObj(std::ostream &os);

public:
    message(const std::string &m);
    ~message();

    friend std::ostream &operator<<(std::ostream &os, message &obj);
};
