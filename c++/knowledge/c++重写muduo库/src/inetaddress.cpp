/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 15:12:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-05 15:28:53
 * @FilePath: /c++/knowledge/c++重写muduo库/src/inetaddress.cpp
 * @Description: 注释信息
 */
#include "inetaddress.h"

namespace ocean_muduo
{

    inetaddress::inetaddress(/* args */)
    {
    }

    inetaddress::~inetaddress()
    {
    }

    inetaddress::inetaddress(uint16_t port, std::string ip) {}

    inetaddress::inetaddress(const sockaddr_in &addr) : addr_(addr) {}

    std::string inetaddress::to_ip() const {}

    std::string inetaddress::to_ip_port() const {}

    uint16_t inetaddress::to_port() const {}

    const sockaddr_in *inetaddress::get_sock_addr() const
    {
        return &addr_;
    }
} // namespace ocean_muduo
