/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-15 15:01:52
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 07:10:48
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/ocean_mprpc_channel.cc
 * @Description: 注释信息
 */
#include "ocean_mprpc_channel.h"
#include "ocean_mprpc_application.h"
#include "rpcheader.pb.h"

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

OCEANMprpcChannel::OCEANMprpcChannel(/* args */)
{
}

OCEANMprpcChannel::~OCEANMprpcChannel()
{
}

// 所有通过stub代理对象调用的rpc方法， 统一做rpc方法调用的数据序列化和网络发送
// header_size + service_name + method_name + args_size + args
void OCEANMprpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method, google::protobuf::RpcController *controller, const google::protobuf::Message *request, google::protobuf::Message *response, google::protobuf::Closure *done)
{
    const google::protobuf::ServiceDescriptor *sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    // 获取参数的序列化字符串长度 args_size
    int args_size = 0;
    std::string args_str;
    if (request->SerializeToString(&args_str)) // request序列化
    {
        args_size = args_str.size();
    }
    else
    {
        std::cout << "serialize request error!\n";
        return;
    }

    // 定义rpc的请求header
    ocean_mprpc::RpcHeader rpc_header;
    rpc_header.set_service_name(service_name);
    rpc_header.set_method_name(method_name);
    rpc_header.set_args_size(args_size);

    uint32_t header_size = 0;
    std::string rpc_header_str;
    if (rpc_header.SerializeToString(&rpc_header_str)) // rpc_header序列化
    {
        header_size = rpc_header_str.size();
    }
    else
    {
        std::cout << "serialize rpc_header to rpc_header_str error!\n";
        return;
    }

    // 组织待发送的rpc请求字符串
    std::string send_rpc_str;
    send_rpc_str.insert(0, std::string((char *)&header_size, 4)); // header_size
    send_rpc_str += rpc_header_str;
    send_rpc_str += args_str;

    // 打印调式信息
    std::cout << "===========================================================\n";
    std::cout << "OCEANMprpcChannel::CallMethod\n";
    std::cout << "header_size: " << header_size << "\n";
    std::cout << "rpc_header_str: " << rpc_header_str << "\n";
    std::cout << "service_name: " << service_name << "\n";
    std::cout << "method_name: " << method_name << "\n";
    std::cout << "args_str: " << args_str << "\n";
    std::cout << "send_rpc_str: " << send_rpc_str << "\n";
    std::cout << "===========================================================\n";

    // 使用tcp编程， 完成rpc方法的调用
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error: " << errno << "\n";
        exit(EXIT_FAILURE);
    }

    // 读取配置文件rpcserver的信息
    std::string ip = OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 发起连接rpc服务节点
    if (connect(clientfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "connet error: " << errno << "\n";
        exit(EXIT_FAILURE);
    }

    // 发送rpc服务请求
    if (send(clientfd, send_rpc_str.c_str(), send_rpc_str.size(), 0) == -1)
    {
        std::cout << "send error: " << errno << "\n";
        close(clientfd);
    }

    // 接收rpc服务的响应值
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if ((recv_size = recv(clientfd, recv_buf, 1024, 0)) == -1)
    {
        std::cout << "recv error: " << errno << "\n";
        close(clientfd);
        return;
    }

    // std::string response_str(recv_buf, 0, recv_size); // 由于recv_buf 在处理的过程中，遇到0就结束，导致异常 放弃该转换方法
    // if (!response->ParseFromString(response_str)) // 解析response_str
    if(!response->ParseFromArray(recv_buf,recv_size))
    {
        std::cout << "response parse response_str error: " << errno << "\n";
        close(clientfd);
        return;
    }

    close(clientfd);
}
