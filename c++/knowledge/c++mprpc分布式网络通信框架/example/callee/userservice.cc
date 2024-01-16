/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 16:57:33
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 08:54:17
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/example/callee/userservice.cc
 * @Description: 注释信息
 */
#include <iostream>
#include <string>

#include "../user.pb.h"
#include "../rescode.pb.h"
#include "ocean_mprpc_application.h"
#include "rpc_provider.h"

/**
 * @brief UserService原本是一个本地服务，提供了两个进程内的本地方法， Login和GetFriendList
 *
 */
class UserService : public ocean_mprpc::UserServiceRpc // 使用在rpc服务发布端（rpc服务提供者）
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login"
                  << "\n";
        std::cout << "name:" << name
                  << "\n";
        std::cout << "pwd:" << pwd
                  << "\n";
        return true;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register"
                  << "\n";
        std::cout << "id:" << id
                  << "\n";
        std::cout << "name:" << name
                  << "\n";
        std::cout << "pwd:" << pwd
                  << "\n";
        return true;
    }

    // 重写基类UserServiceRpc的虚函数， 下面的方法是由框架直接调用的
    /**
     * 1. caller ---发送请求--->  Login(LoginRequest)   ====> muduo ------>callee
     * 2. callee --->处理Login(LoginRequest) ---交到下面重写的Login方法
     */
    void Login(::google::protobuf::RpcController *controller,
               const ::ocean_mprpc::LoginRequest *request,
               ::ocean_mprpc::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        // 框架给业务上报了，请求参数LoginRequest，  应用获取相应数据做本地业务
        std::cout << "doing rpc service: Login"
                  << "\n";
        // 解析LoginRequest
        std::string name = request->name();
        std::string pwd = request->pwd();
        // 做本地业务
        bool login_res = Login(name, pwd);
        //  把相应写入LoginResponse
        ocean_mprpc::ResultCode *code = response->mutable_res();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_res);

        // 执行回调操作，   执行相应对象数据的序列化和网络发送，  都是由框架来完成的
        done->Run();
    }

    void Register(google::protobuf::RpcController *controller,
                  const ocean_mprpc::RegisterRequest *request,
                  ocean_mprpc::RegisterResponse *response,
                  google::protobuf::Closure *done)
    {
        std::cout << "doing rpc service: Register\n";
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool register_res = Register(id, name, pwd); // 做本地业务
        // 将结果写入response
        ocean_mprpc::ResultCode *code = response->mutable_res();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(register_res);

        // 执行回调操作
        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 常规本进程调用
    // UserService us;
    // us.Login("xxx","xxx");

    // 调用RPC框架的初始化操作
    OCEANMprpcApplication::Init(argc, argv);
    // provider 是一个rpc网络服务对象
    RpcProvider provider;
    // 把UserService对象发布到rpc节点上
    provider.NotifyService(new UserService());
    // 启动一个rpc服务发布节点， Run()以后， 进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}