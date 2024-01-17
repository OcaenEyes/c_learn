/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 11:37:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 21:45:54
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/zookeeper_util.cc
 * @Description: 注释信息
 */

#include "zookeeper_util.h"
#include "ocean_mprpc_application.h"

#include <semaphore.h>
#include <iostream>

// 全局的watcher函数，  zkserver  给zkclient 发送通知
void global_watcher(zhandle_t *zh, int type,
                    int state, const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT) // 回调的消息类型 和 会话相关的消息类型
    {
        if (state == ZOO_CONNECTED_STATE) // zkclient 连接 zkserver成功
        {
            sem_t *sem = (sem_t *)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

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

    // zookeeper_mt：多线程版本
    //    zookeeper的API客户端程序提供了三个线程
    //      1）API调用线程
    //      2）网络I/O线程
    //      3）watcher回调线程

    m_zhandle = zookeeper_init(connstr.c_str(), global_watcher, 3000, nullptr, nullptr, 0);
    if (m_zhandle == nullptr)
    { // !=nullptr的时候仅仅 表示m_zhandle句柄创建成功，不代表连接成功
        std::cout << "zookeeper_init error!\n";
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem); // 给句柄添加额外的信息

    sem_wait(&sem); // 等待sem信号量变化
    std::cout << "zookeeper_init success!\n";
}

void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buf[128];
    int path_buf_len = sizeof(path_buf);
    int flag;

    // 先判断path表示的znode节点是否存在，如果存在，就不再重复创建了
    flag = zoo_exists(m_zhandle, path, 0, nullptr);

    if (flag == ZNONODE) // 表示path的znode节点不存在
    {
        // 创建指定path的znode节点
        flag = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buf, path_buf_len);
        if (flag == ZOK)
        {
            std::cout << "znode create success ...path:" << path << "\n";
        }
        else
        {
            std::cout << "flag:" << flag << "\n";
            std::cout << "znode create error ...path:" << path << "\n";
            exit(EXIT_FAILURE);
        }
    }
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
