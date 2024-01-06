/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 03:25:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-05 08:03:24
 * @FilePath: /c++/knowledge/c++重写muduo库/src/main.cpp
 * @Description: 注释信息
 */

#include "logger.h"
#include "timestamp.h"
#include "inetaddress.h"

int main()
{
    std::cout << ocean_muduo::timestamp::now().to_string() << "\n";

    ocean_muduo::logger::instance().log("测试一下");

    ocean_muduo::inetaddress addr111(8080);
    std::cout << addr111.to_ip() << "\n";
    std::cout << addr111.to_port() << "\n";
    std::cout << addr111.to_ip_port() << "\n";


    return 0;
}