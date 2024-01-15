<!--
 * @Author: OCEAN.GZY
 * @Date: 2024-01-15 08:11:04
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-15 08:13:38
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/readme.md
 * @Description: 注释信息
-->

# mprpc分布式网络通信框架

## 技术栈
- 集群和分布式概念以及原理
- RPC远程过程调用原理以及实现
- Protobuf数据序列化和反序列化协议
- ZooKeeper分布式一致性协调服务应用以及编程
- muduo网络库编程
- conf配置文件读取
- 异步日志
- CMake构建项目集成编译环境
- github管理项目


## 集群和分布式
- 集群：每一台服务器独立运行一个工程的所有模块。
- 分布式：一个工程拆分了很多模块，每一个模块独立部署运行在一个服务器主机上，所有服务器协同工作共同提供服务，每一台服务器称作分布式的一个节点，根据节点的并发要求，对一个节点可以再做节点模块集群部署。

## RPC通信原理
RPC（Remote Procedure Call Protocol）远程过程调用协议。



```
class UserService: public UserServiceRpc
{
    login <=== 本地方法
    login <===== 重写protobuf提供的virtual虚函数
    {
        1.从LoginRequest获取参数的值
        2.调用本地方法login，并获取返回值
        3.用上面 的返回值填写LoginResponse
        4.一个回调，把LoginResponse序列化发送给rpc client
    }
}

```