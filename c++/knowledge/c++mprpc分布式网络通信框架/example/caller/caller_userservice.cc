/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-15 15:13:17
 * @LastEditors: OCEAN.GZY
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/example/caller/caller_userservice.cc
 * @Description: 注释信息
 */
#include <iostream>

#include "ocean_mprpc_application.h"
#include "ocean_mprpc_channel.h"
#include "../user.pb.h"
#include "../rescode.pb.h"

int main(int argc, char **argv)
{
    // 整个程序启动后， 想使用ocean_mprpc框架来享受rpc服务调用， 一定要先调用框架的初始化函数（只初始化一次）
    OCEANMprpcApplication::Init(argc, argv);

    std::unique_ptr<OCEANMprpcChannel> channel(new OCEANMprpcChannel());
    // 演示调用远程发布的rpc方法Login
    ocean_mprpc::UserServiceRpc_Stub user_stub(&*channel);

    // rpc方法的请求参数
    ocean_mprpc::LoginRequest request;
    request.set_name("gzy");
    request.set_pwd("123456");
    // rpc方法的响应
    ocean_mprpc::LoginResponse response;
    // 发起rpc方法的调用， 同步的rpc调用， OCEANMprpcChannel::CallMethod
    user_stub.Login(nullptr, &request, &response, nullptr); // RpcChannel中继  ---> 调用的是 OCEANMprpcChannel::CallMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (response.res().errcode() == 0)
    {
        std::cout << "rpc login response success: " << response.success() << "\n";
    }
    else
    {
        std::cout << "rpc login response error: " << response.res().errmsg() << "\n";
    }

    ocean_mprpc::RegisterRequest reg_req;
    ocean_mprpc::RegisterResponse reg_res;
    reg_req.set_id(1000);
    reg_req.set_name("gzy");
    reg_req.set_pwd("123456");
    user_stub.Register(nullptr, &reg_req, &reg_res, nullptr);
    if (reg_res.res().errcode() == 0)
    {
        std::cout << "rpc register response success: " << reg_res.success() << "\n";
    }
    else
    {
        std::cout << "rpc register response error: " << reg_res.res().errmsg() << "\n";
    }

    return 0;
}