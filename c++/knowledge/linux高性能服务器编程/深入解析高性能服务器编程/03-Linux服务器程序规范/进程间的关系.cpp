/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 19:18:41
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 19:25:31
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/03-Linux服务器程序规范/进程间的关系.cpp
 * @Description: 注释信息
 */
#include <unistd.h>

// 每个进程都隶属于一个进程组； 每个进程组都有一个首领进程，其PGID和PID相同,进程组将一直存在，直到其中所有进程都退出 或加入其他进程组

/**
 * @description:  获取指定进程的PGID
 * @param {pid_t} pid
 * @return {*} 成功则返回pgid，失败则返回-1并设置errno
 */
pid_t getpgid(pid_t pid) {}

/**
 * @description: 设置PGID
 * @param {pid_t} pid
 * @param {pid_t} pgid
 * @return {*}
 */
int setpgid(pid_t pid, pid_t pgid) {}


// 会话
// 一些关联的进程组形成一个会话 session

/**
 * @description: 创建一个会话； 该函数不能由进程组的首领进程调用否则将产生错误
 *              - 非首领进程调用该函数不仅创建新会话， 还
 *                - 调用进程成为会话的首领，此时该进程是新会话的唯一成员
 *                - 新建一个进程组，其PGID就是调用进程的PID，调用进程成为该组的首领
 *                - 调用进程将甩开终端(如果有的话)  
 * @return {*} 成功则返回新的进程组PGID，失败则返回-1并设置errno
 */
pid_t setsid(void){}