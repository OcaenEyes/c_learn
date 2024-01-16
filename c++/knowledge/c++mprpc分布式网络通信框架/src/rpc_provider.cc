/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-14 12:57:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-16 03:44:17
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/rpc_provider.cc
 * @Description: 注释信息
 */
#include "rpc_provider.h"
#include "ocean_mprpc_application.h"
#include "rpcheader.pb.h"

#include <functional>
#include <google/protobuf/descriptor.h>

RpcProvider::RpcProvider(/* args */)
{
}

RpcProvider::~RpcProvider()
{
}

// 这里是框架提供给外部使用，可以发布rpc方法的函数接口
/**
 * service_name ===>对应 service描述
 *                  ===>  service* 记录服务对象
 *                      ===>  method_name 对应方法描述
 *                            ===> method 方法对象
 */
void RpcProvider::NotifyService(google::protobuf::Service *servcie)
{
    ServiceInfo servcie_info;

    // 获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor *p_service_desc = servcie->GetDescriptor();

    // 获取服务对象的名字
    std::string service_name = p_service_desc->name();
    // 获取服务对象service的方法数量
    int method_cnt = p_service_desc->method_count();

    std::cout << "service_name:" << service_name << "\n";

    for (int i = 0; i < method_cnt; i++)
    {
        // 获取服务对象 指定下标的服务方法的描述（抽象的描述）
        const google::protobuf::MethodDescriptor *p_method_desc = p_service_desc->method(i);
        std::string method_name = p_method_desc->name();
        std::cout << "method_name:" << method_name << "\n";
        servcie_info.m_method_map.insert({method_name, p_method_desc});
    }

    servcie_info.m_service = servcie;
    m_service_map.insert({service_name, servcie_info});
}

// 启动rpc服务节点，开始提供rpc远程调用服务
void RpcProvider::Run()
{
    std::string ip = OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(OCEANMprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    muduo::net::InetAddress addres(ip, port);

    // 创建 TcpServer对象
    muduo::net::TcpServer tcpserver(&m_eventloop, addres, "RpcProvider");

    // 绑定连接回调 和消息读写回调方法【分离网络代码 和 业务代码】
    tcpserver.setConnectionCallback(std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    tcpserver.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库的线程数量
    tcpserver.setThreadNum(3);

    std::cout << "RpcProvider run at ip: " << ip << " port: " << port << "\n";

    // 启动网络服务
    tcpserver.start();
    m_eventloop.loop();
}

// 新的socket连接回调
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        // 和rpc client 的连接断开了
        conn->shutdown();
    }
}

/**
 * 在框架内部， RpcProvider 和RpcConsumer协商好之间通信用的 protobuf数据类型
 *   service_name  、 method_name 、args ---> 在框架中定义proto的message类型，进行数据头的序列化和反序列化【数据头记录service_name、method_name、args_size】
 *   其中head_size(4个字节) + header_str() + arg_str
 *    std::string 的insert 和 copy方法
 *
 */
// 已建立连接用户的读写事件回调， 如果远程有一个rpc服务的调用请求，那么onMessage方法就会响应
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp receive_time)
{
    // 网络上接收的远程rpc调用请求的字符流 ， 譬如 login args
    std::string recv_buf = buffer->retrieveAllAsString();

    // 从字符流中读取前4个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char *)&header_size, 4, 0);

    // 根据header_size 读取数据头的原始字符流   ,反序列化数据， 得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4, header_size);
    ocean_mprpc::RpcHeader rpc_header;

    std::string service_name;
    std::string method_name;
    uint32_t args_size;

    if (rpc_header.ParseFromString(rpc_header_str))
    {
        // 数据头反序列化成功
        service_name = rpc_header.service_name();
        method_name = rpc_header.method_name();
        args_size = rpc_header.args_size();
    }
    else
    {
        // 数据头反序列化失败
        std::cout << "rpc_header_str:" << rpc_header_str << " parse failed!\n";
        return;
    }

    // 获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印调式信息
    std::cout << "===========================================================\n";
    std::cout << "RpcProvider::onMessage\n";
    std::cout << "header_size: " << header_size << "\n";
    std::cout << "rpc_header_str: " << rpc_header_str << "\n";
    std::cout << "service_name: " << service_name << "\n";
    std::cout << "method_name: " << method_name << "\n";
    std::cout << "args_str: " << args_str << "\n";
    std::cout << "===========================================================\n";

    // 获取service对象和 method对象
    auto it = m_service_map.find(service_name);
    if (it == m_service_map.end())
    {
        std::cout << service_name << "is not exist!\n";
        return;
    }

    auto mit = it->second.m_method_map.find(method_name);
    if (mit == it->second.m_method_map.end())
    {
        std::cout << service_name << ":" << method_name << "is not exist!\n";
        return;
    }

    google::protobuf::Service *service = it->second.m_service;      // 获取service对象
    const google::protobuf::MethodDescriptor *method = mit->second; // 获取method对象

    // 生成rpc方法调用的请求request和相应response参数
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str))
    {
        std::cout << "request parse error, content:" << args_str << "\n";
        return;
    }

    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 给下面的method方法调用，绑定一个Closure的回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider, const muduo::net::TcpConnectionPtr &, google::protobuf::Message *>(this, &RpcProvider::SendRpcResponse, conn, response);

    // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    service->CallMethod(method, nullptr, request, response, done);
}

// Closure的回调操作，用于序列化rpc的响应和网络发送
void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr &conn, google::protobuf::Message *response)
{
    std::string response_str;
    if (response->SerializeToString(&response_str)) // response进行序列化
    {
        // 序列化成功后， 通过网络把rpc方法执行的结果 发送给rpc调用放
        conn->send(response_str);
    }
    else
    {
        std::cout << " serialize response_str:" << response_str << " failed!\n";
    }

    conn->shutdown(); // 模拟http的短链接服务， 由rpcprovider主动断开连接
}
