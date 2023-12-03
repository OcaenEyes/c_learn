/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 19:09:48
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 19:16:45
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/03-Linux服务器程序规范/用户信息-UID-EUID-GID-EGID.cpp
 * @Description: 注释信息
 */
#include <sys/types.h>
#include <unistd.h>

uid_t getuid() {}  // 获取真实用户ID --- 启动应用程序的用户的id
uid_t geteuid() {} // 获取有效用户ID --- root账户(文件所有者)的id

gid_t getgid() {}  // 获取真实组ID
gid_t getegid() {} // 获取有效组ID

int setuid(uid_t uid) {}  // 设置真实用户ID
int seteuid(uid_t uid) {} // 设置有效用户ID  ， 设置方便资源访问，使运行程序的用户拥有该程序的有效用户的权限

int setgid(gid_t gid) {}  // 设置真实组ID
int setegid(gid_t gid) {} // 设置有效组ID