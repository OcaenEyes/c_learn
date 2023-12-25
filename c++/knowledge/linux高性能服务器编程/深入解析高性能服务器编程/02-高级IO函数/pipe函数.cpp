/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-01 21:20:44
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-01 21:26:03
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/pipe函数.cpp
 * @Description: 注释信息
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

/// @brief  pipe 创建一个管道，已实现进程间通信
/// @param fd 是一个包含2个int型整数的数组指针
/// @return 成功则返回0，并将一对打开的文件描述符值填入其参数指向的数组； 如果失败则返回-1并设置errno
/// fd[1]写入的数据fd[0]读出
int pipe(int fd[2]) {}

/* 双向管道socketpair */
/// @brief 
/// @param domain 只能使用UNIX本地域协议族AF_UNIX
/// @param type 
/// @param protocol 
/// @param fd 
/// @return 
int socketpair(int domain, int type, int protocol, int fd[2]) {}