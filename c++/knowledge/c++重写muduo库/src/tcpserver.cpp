#include "tcpserver.h"
#include "logger.h"

namespace ocean_muduo
{
    eventloop *check_loop_not_null(eventloop *loop)
    {
        if (loop == nullptr)
        {
            LOG_FATAL("%s:%s:%d mainloop is null!\n", __FILE__, __FUNCTION__, __LINE__);
        }
        return loop;
    }

    tcpserver::tcpserver(eventloop *loop, const inetaddress &listen_addr, const std::string &name, Option opt)
        : loop_(check_loop_not_null(loop)),
          ip_port_(listen_addr.to_ip_port()),
          name_(name),
          acceptor_(new acceptor(loop, listen_addr, opt)),
          thread_pool_(new eventloop_thread_pool(loop, name)),
          connection_callback_(),
          message_callback_(),
          next_conn_id_(1),
          started_(0)
    {
    }

    tcpserver::~tcpserver()
    {
    }

    void tcpserver::set_thread_init_callback(const std::function<void(eventloop *)> &cb)
    {
    }

    void tcpserver::set_connection_callback(const ConnectionCallback &cb)
    {
    }

    void tcpserver::set_message_callback(const MessageCallback &cb)
    {
    }

    void tcpserver::set_write_callback(const WriteCallback &cb)
    {
    }

    void tcpserver::set_thread_num(int num)
    {
    }

    void tcpserver::start()
    {
    }

    void tcpserver::new_connection(int sockfd, const inetaddress &peer_addr)
    {
    }

    void tcpserver::remove_connection(const TcpConnectionPtr &conn)
    {
    }

} // namespace ocean_muduo