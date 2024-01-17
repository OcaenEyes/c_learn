/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 11:37:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 11:54:12
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/zookeeper_util.cc
 * @Description: 注释信息
 */

#include "zookeeper_util.h"
#include "ocean_mprpc_application.h"

#include <semaphore.h>
#include <iostream>

ZkClient::ZkClient(/* args */) : m_zhandle(nullptr)
{
}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle); // 关闭句柄， 释放资源，
    }
}

// 连接zk server
void ZkClient::Start()
{
    std::string host = OCEANMprpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port = OCEANMprpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    std::string connstr = host + ":" + port;
}

void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
}

// 根据指定的path，获取znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buf[64];
    int buflen = sizeof(buf);
    int flag = zoo_get(m_zhandle, path, 0, buf, &buflen, nullptr);
    if (flag != ZOK)
    {
        std::cout << "get znode from path: " << path << "error\n";
        return "";
    }
    else
    {
        return buf;
    }
}
