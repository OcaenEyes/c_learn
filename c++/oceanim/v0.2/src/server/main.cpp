/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-14 01:34:00
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-14 01:36:09
 * @FilePath: /c++/oceanim/v0.2/src/server/main.cpp
 * @Description: 注释信息
 */
#include "oceanim_server.h"
#include "oceanim_service.h"
#include <iostream>
#include <signal.h>

// 处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    OceanIMService::instance()->reset();
    exit(0);
}

int main()
{
    signal(SIGINT, resetHandler);
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 12345);
    OceanIMServer imserver(&loop, addr, "OceanIMServer");

    imserver.start();
    loop.loop();

    return 0;
}