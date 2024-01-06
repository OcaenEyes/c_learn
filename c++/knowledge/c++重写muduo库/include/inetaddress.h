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
    };

} // namespace ocean_muduo
