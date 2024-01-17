/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 21:16:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 21:16:41
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/zookeeper_util.h
 * @Description: 注释信息
 */
#pragma once

#include <zookeeper/zookeeper.h>
#include <string>

class ZkClient
{
private:
    // zk的客户端句柄
    zhandle_t *m_zhandle;

public:
    ZkClient(/* args */);
    ~ZkClient();

    // zkclient 启动连接zkserver
    void Start();
    // 在zkserver上根据指定的path创建znode节点
    void Create(const char *path, const char *data, int datalen, int state = 0);
    // 根据参数指定的znode节点路径，获取znode节点的值
    std::string GetData(const char *path);
};
