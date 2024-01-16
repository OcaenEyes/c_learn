/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-16 11:44:05
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 14:17:57
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/ocean_mprpc_controller.cc
 * @Description: 注释信息
 */

#include "ocean_mprpc_controller.h"

OCEANMprpcController::OCEANMprpcController()
{
    m_failed = false;
    m_errtext = "";
}

OCEANMprpcController::~OCEANMprpcController()
{
}

void OCEANMprpcController::Reset()
{
    m_failed = false;
    m_errtext = "";
}

bool OCEANMprpcController::Failed() const
{
    return m_failed;
}

std::string OCEANMprpcController::ErrorText() const
{
    return m_errtext;
}

void OCEANMprpcController::SetFailed(const std::string &reason)
{
    m_failed = true;
    m_errtext = reason;
}

void OCEANMprpcController::StartCancel()
{
}

bool OCEANMprpcController::IsCanceled() const
{
    return false;
}

void OCEANMprpcController::NotifyOnCancel(google::protobuf::Closure *callback)
{
}
