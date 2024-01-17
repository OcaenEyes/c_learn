/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-16 08:50:39
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 06:01:24
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/example/callee/friendservice.cc
 * @Description: 注释信息
 */
#include <iostream>
#include <string>

#include "../friend.pb.h"
#include "../rescode.pb.h"
#include "ocean_mprpc_application.h"
#include "rpc_provider.h"
#include "ocean_logger.h"

class FriendService : public ocean_mprpc::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendList(uint32_t userid)
    {
        std::cout << "doing local service: GetFriendList"
                  << "\n";
        std::cout << "userid:" << userid
                  << "\n";
        std::vector<std::string> res;
        res.emplace_back("gzy01");
        res.emplace_back("gzy02");
        res.emplace_back("gzy03");
        return res;
    }

    void GetFriendList(google::protobuf::RpcController *controller,
                       const ocean_mprpc::GetFriendListRequest *request,
                       ocean_mprpc::GetFriendListReponse *response,
                       google::protobuf::Closure *done)
    {
        std::cout << "doing rpc service: GetFriendList\n";
        uint32_t userid = request->userid();
        std::vector<std::string> friends_res = GetFriendList(userid);

        // 将结果写入response
        ocean_mprpc::ResultCode *code = response->mutable_res();
        code->set_errcode(0);
        code->set_errmsg("");
        for (auto &&i : friends_res)
        {
            std::string *p = response->add_friends();
            *p = i;
        }

        done->Run(); // 执行回调
    }
};

int main(int argc, char **argv)
{
    // 常规本进程调用
    // UserService us;
    // us.Login("xxx","xxx");
    LOG_INFO("first log message!");
    LOG_ERROR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);

    // 调用RPC框架的初始化操作
    OCEANMprpcApplication::Init(argc, argv);
    // provider 是一个rpc网络服务对象
    RpcProvider provider;
    // 把UserService对象发布到rpc节点上
    provider.NotifyService(new FriendService());
    // 启动一个rpc服务发布节点， Run()以后， 进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}