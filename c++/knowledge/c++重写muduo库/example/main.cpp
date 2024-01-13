/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 03:25:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-13 10:19:32
 * @FilePath: /c++/knowledge/c++重写muduo库/example/main.cpp
 * @Description: 注释信息
 */

#include "../output/ocean_muduo/include/tcpserver.h"
#include "../output/ocean_muduo/include/logger.h"

class oceanserver
{
private:
    ocean_muduo::eventloop *loop_;
    ocean_muduo::tcpserver server_;

    void on_message(const ocean_muduo::TcpConnectionPtr &conn, ocean_muduo::buffer *buf, ocean_muduo::timestamp time)
    {
        printf("on_message!\n");
        std::string msg = buf->retrieve_all_asstring();
        conn->send(msg);
        conn->shutdown(); // 写端   EPOLLHUP =》 closeCallback_
    }

    void on_connect(const ocean_muduo::TcpConnectionPtr &conn)
    {
        printf("on_connect!\n");
        if (conn->get_connected())
        {
            LOG_INFO("connection up : %s", conn->get_peer_addr().to_ip_port().c_str());
        }
        else
        {
           LOG_INFO("connection down : %s", conn->get_peer_addr().to_ip_port().c_str());
        }
    }

public:
    oceanserver(ocean_muduo::eventloop *loop, const ocean_muduo::inetaddress &addr, const std::string &name) : server_(loop, addr, name), loop_(loop)
    {
        // 注册回调函数
        server_.set_connection_callback(std::bind(&oceanserver::on_connect,this,std::placeholders::_1));
        server_.set_message_callback(std::bind(&oceanserver::on_message,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        server_.set_thread_num(3);
    }
    ~oceanserver() {}

    void start()
    {
        server_.start();
    }
};

int main()
{
    ocean_muduo::eventloop loop;
    ocean_muduo::inetaddress addr(8000);
    oceanserver server(&loop, addr, "OceanServer-01"); // Acceptor non-blocking listenfd  create bind
    server.start();                                   // listen  loopthread  listenfd => acceptChannel => mainLoop =>
    loop.loop();                                      // 启动mainLoop的底层Poller

    return 0;
}