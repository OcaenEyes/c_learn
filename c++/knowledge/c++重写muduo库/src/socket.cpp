/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 02:41:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 07:05:26
 * @FilePath: /c++/knowledge/c++重写muduo库/src/socket.cpp
 * @Description: 注释信息
 */
#include "socket.h"
#include "inetaddress.h"
#include "logger.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <netinet/tcp.h>

namespace ocean_muduo
{

    socket::socket(int sockfd) : sockfd_(sockfd)
    {
    }

    socket::~socket()
    {
        close(sockfd_);
    }

    int socket::get_fd() const
    {
        return sockfd_;
    }

    void socket::bind_address(const inetaddress *localaddr)
    {
        int ret = ::bind(sockfd_, (sockaddr *)localaddr->get_sock_addr(), sizeof(sockaddr_in));
        if (ret != 0)
        {
            LOG_FATAL("bind sockfd_: %d fail!\n", sockfd_);
        }
    }

    void socket::listen()
    {
        int ret = ::listen(sockfd_, 1024);
        if (ret != 0)
        {
            LOG_FATAL("listen sockfd_: %d fail!\n", sockfd_);
        }
    }

    int socket::accept(inetaddress *peeraddr)
    {
        sockaddr_in addr;
        socklen_t len;
        bzero(&addr, sizeof(addr));
        int connfd = ::accept(sockfd_, (sockaddr *)&addr, &len);
        if (connfd >= 0)
        {
            peeraddr->set_sock_addr(addr);
        }

        return connfd;
    }

    void socket::shutdown_write()
    {
        if (::shutdown(sockfd_, SHUT_WR) < 0)
        {
            LOG_ERROR("socket::shutdown_write error! errno: %d\n", errno);
        }
    }

    void socket::set_tcp_no_delay(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
    }

    void socket::set_reuse_addr(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    }

    void socket::set_reuse_port(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    }

    void socket::set_keep_alive(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
    }

} // namespace ocean_muduo
