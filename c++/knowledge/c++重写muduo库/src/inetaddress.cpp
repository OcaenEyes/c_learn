/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 15:12:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 03:32:04
 * @FilePath: /c++/knowledge/c++重写muduo库/src/inetaddress.cpp
 * @Description: 注释信息
 */
#include "inetaddress.h"

#include <strings.h>

namespace ocean_muduo
{

    // 构造函数
    inetaddress::inetaddress(/* args */)
    {
    }
    // 析构函数
    inetaddress::~inetaddress()
    {
    }

    // 有参构造
    inetaddress::inetaddress(uint16_t port, std::string ip)
    {
        bzero(&addr_, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    }

    // 有参构造
    inetaddress::inetaddress(const sockaddr_in &addr) : addr_(addr) {}

    std::string inetaddress::to_ip() const
    {
        // 从addr_中读取出ip地址
        return inet_ntoa(addr_.sin_addr);
        // 或者使用inet_ntop
        // char ip[INET_ADDRSTRLEN];
        // inet_ntop(AF_INET, &addr_.sin_addr, ip, INET_ADDRSTRLEN);
        // return ip;
    }

    std::string inetaddress::to_ip_port() const
    {
        // 从addr_中读取出ip地址和port端口
        return std::string(to_ip()) + ":" + std::to_string(to_port());
    }

    uint16_t inetaddress::to_port() const
    {
        // 从addr_中读取出port端口
        return ntohs(addr_.sin_port);
    }

    const sockaddr_in *inetaddress::get_sock_addr() const
    {
        return &addr_;
    }

    void inetaddress::set_sock_addr(const sockaddr_in &addr)
    {
        addr_ = addr;
    }
} // namespace ocean_muduo
