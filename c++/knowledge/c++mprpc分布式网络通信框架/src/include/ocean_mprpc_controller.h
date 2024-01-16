/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-16 21:33:05
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 14:30:30
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/ocean_mprpc_controller.h
 * @Description: 注释信息
 */
#pragma once

#include <string>
#include <google/protobuf/service.h>

class OCEANMprpcController : public google::protobuf::RpcController
{
private:
    bool m_failed;         // rpc方法执行过程中的状态
    std::string m_errtext; // rpc方法执行过程中的错误信息
public:
    OCEANMprpcController(/* args */);
    ~OCEANMprpcController();

    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string &reason);

    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);
};