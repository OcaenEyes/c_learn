#include "acceptor.h"
#include "inetaddress.h"
#include "logger.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

namespace ocean_muduo
{
    static int create_nonblocking()
    {
        int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        if (sockfd < 0)
        {
            LOG_FATAL("%s:%s:%d listen socket create error: %d !\n", __FILE__, __FUNCTION__, __LINE__, errno);
        }
        return sockfd;
    }

    acceptor::acceptor(eventloop *loop, const inetaddress &listen_addr, bool reuse_port)
        : loop_(loop),
          accept_socket_(create_nonblocking()),
          accept_channel_(loop, accept_socket_.get_fd()),
          listenning_(false)
    {
        accept_socket_.set_reuse_addr(true);
        accept_socket_.set_reuse_port(reuse_port);
        accept_socket_.bind_address(&listen_addr);

        // baseloop 监听到 accept_channel_（listenfd）有事件发生时 调用handle_read 回调
        accept_channel_.set_read_callback(std::bind(&acceptor::handle_read, this));
    }

    acceptor::~acceptor()
    {
        accept_channel_.disable_all();
        accept_channel_.remove();
    }

    void acceptor::set_new_connection_callback(const std::function<void(int, const inetaddress &)> &cb)
    {
    }

    bool acceptor::get_listenning() const
    {
        return listenning_;
    }

    void acceptor::listen()
    {
        listenning_ =true;
        accept_socket_.listen(); // 开启listen
        accept_channel_.enable_reading(); // accept_channel_ 

    }

    // 当listenfd有事件发生了，就是有新用户连接了
    void acceptor::handle_read()
    {
        inetaddress peeraddr; // 对应的客户端地址
        int connfd = accept_socket_.accept(&peeraddr);
        if (connfd >= 0)
        {
            if (new_connection_callback_)
            {
                new_connection_callback_(connfd, peeraddr);
            }
            else
            {
                ::close(connfd);
            }
        }
        else
        {
            LOG_ERROR("%s:%s:%d accept error: %d !\n", __FILE__, __FUNCTION__, __LINE__, errno);
            if (errno == EMFILE)
            {
                // EMFILE The per-process limit on the number of open file descriptors has been reached.
                LOG_ERROR("%s:%s:%d sockfd reached limited ,server need expansion, accept error:  %d !\n", __FILE__, __FUNCTION__, __LINE__, errno);
            }
        }
    }

} // namespace ocean_muduo
