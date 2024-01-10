#pragma once

#include "noncopyable.h"
#include "socket.h"
#include "channel.h"

#include <functional>

namespace ocean_muduo
{
    class eventloop;
    class inetaddress;

    /**
     * @brief 运行在mainloop内【baseloop】
     *
     */
    class acceptor : public noncopyable
    {

    public:
        // using NewConnectionCallback = std::function<void(int, const inetaddress &)>;
        acceptor(eventloop *loop, const inetaddress &listen_addr, bool reuse_port);
        ~acceptor();

        void set_new_connection_callback(const std::function<void(int, const inetaddress &)> &cb);
        bool get_listenning() const;
        void listen();

    private:
        eventloop *loop_;
        socket accept_socket_;
        channel accept_channel_;
        std::function<void(int, const inetaddress &)> new_connection_callback_;
        bool listenning_;

        void handle_read();
    };

} // namespace ocean_muduo
