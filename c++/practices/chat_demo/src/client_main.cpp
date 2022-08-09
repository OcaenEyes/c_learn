/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 22:36:15
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 22:36:15
 * @FilePath: /c++/practices/chat_demo/src/client_main.cpp
 * @Description: 注释信息
 */
#include "client.h"

// 客户端主函数
// 创建客户端对象后 启动客户端
int main(int argc, char *argv[])
{
    client _client;
    _client.start_client();
    return 0;
}