#include "message.h"
#include "iostream"

std::ostream &message::printObj(std::ostream &os)
{
    os << "this is my name:GZY " << std::endl;
    os << m_msg;
    return os;
}

message::message(const std::string &m) : m_msg(m)
{
}

message::~message()
{
}

std::ostream &operator<<(std::ostream &os, message &obj)
{
    return obj.printObj(os);
}
