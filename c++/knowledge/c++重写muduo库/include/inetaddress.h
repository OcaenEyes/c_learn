/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 03:31:30
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 03:31:30
 * @FilePath: /c++/knowledge/c++重写muduo库/include/inetaddress.h
 * @Description: 注释信息
 */
#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>

namespace ocean_muduo
{
    /**
     * @brief 封装socket地址类型
     *
     */
    class inetaddress
    {
    private:
        sockaddr_in addr_;

    public:
        inetaddress(/* args */);
        explicit inetaddress(uint16_t port, std::string ip = "127.0.0.1");
        explicit inetaddress(const sockaddr_in &addr);
        ~inetaddress();

        std::string to_ip() const;
        std::string to_ip_port() const;
        uint16_t to_port() const;

        const sockaddr_in *get_sock_addr() const;
        void set_sock_addr(const sockaddr_in &addr);
    };

} // namespace ocean_muduo
