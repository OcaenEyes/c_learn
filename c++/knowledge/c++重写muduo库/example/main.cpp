/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 03:25:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-12 13:10:10
 * @FilePath: /c++/knowledge/c++重写muduo库/example/main.cpp
 * @Description: 注释信息
 */

#include "tcpserver.h"
#include "logger.h"

class oceanserver
{
private:
    eventloop *loop_;
    tcpserver server_;

    void

public:
    oceanserver(eventloop *loop, const inetaddress &addr, const std::string &name) : server_(loop, addr, name), loop_(loop)
    {
        // 注册回调函数
        server_.set_connection_callback();
        server_.set_message_callback();
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

    return 0;
}