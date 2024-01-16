/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-15 14:57:33
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 03:13:37
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/ocean_mprpc_channel.h
 * @Description: 注释信息
 */
#pragma once

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

class OCEANMprpcChannel : public google::protobuf::RpcChannel
{
private:
    /* data */
public:
    OCEANMprpcChannel(/* args */);
    ~OCEANMprpcChannel();

    // 所有通过stub代理对象调用的rpc方法， 统一做rpc方法调用的数据序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor *method,
                    google::protobuf::RpcController *controller,
                    const google::protobuf::Message *request,
                    google::protobuf::Message *response,
                    google::protobuf::Closure *done);
};
