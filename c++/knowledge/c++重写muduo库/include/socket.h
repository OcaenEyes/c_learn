/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 06:12:04
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-10 06:23:46
 * @FilePath: /c++/knowledge/c++重写muduo库/include/socket.h
 * @Description: 注释信息
 */
#pragma once

#include "noncopyable.h"

namespace ocean_muduo
{

    class inetaddress;

    /**
     * @brief 封装socket
     *
     */
    class socket : public noncopyable
    {
    private:
        const int sockfd_;

    public:
        explicit socket(int sockfd); // 避免隐式构造

        ~socket();

        int get_fd() const;
        void bind_address(const inetaddress *localaddr);
        void listen();
        int accept(inetaddress *peeraddr);

        void shutdown_write();

        void set_tcp_no_delay(bool on);
        void set_reuse_addr(bool on);
        void set_reuse_port(bool on);
        void set_keep_alive(bool on);
    };

} // namespace ocean_muduo
