#include "oceanim_server.h"
#include <iostream>

int main()
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 12345);
    OceanIMServer imserver(&loop, addr, "OceanIMServer");

    imserver.start();
    loop.loop();

    return 0;
}