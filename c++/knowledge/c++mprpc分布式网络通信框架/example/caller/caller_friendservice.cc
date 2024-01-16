
#include <iostream>

#include "ocean_mprpc_application.h"
#include "ocean_mprpc_channel.h"
#include "ocean_mprpc_controller.h"
#include "../friend.pb.h"
#include "../rescode.pb.h"

int main(int argc, char **argv)
{
    // 整个程序启动后， 想使用ocean_mprpc框架来享受rpc服务调用， 一定要先调用框架的初始化函数（只初始化一次）
    OCEANMprpcApplication::Init(argc, argv);

    std::unique_ptr<OCEANMprpcChannel> channel(new OCEANMprpcChannel());

    ocean_mprpc::FriendServiceRpc_Stub friend_stud(&*channel);

    ocean_mprpc::GetFriendListRequest friend_req;
    ocean_mprpc::GetFriendListReponse friend_res;

    friend_req.set_userid(1000);

    OCEANMprpcController controller;
    // 发起rpc方法的调用， 同步的rpc的调用过程
    friend_stud.GetFriendList(&controller, &friend_req, &friend_res, nullptr);

    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << "\n";
    }
    else
    {
        if (friend_res.res().errcode() == 0)
        {
            std::cout << "rpc getfriend response success!\n";
            for (auto &&i : friend_res.friends())
            {
                std::cout << "friend name: " << i << "\n";
            }
        }
        else
        {
            std::cout << "rpc getfriend response success: " << friend_res.res().errmsg() << "\n";
        }
    }

    return 0;
}