/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-06 15:09:14
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-06 15:16:37
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/06-信号/linux信号概述.cpp
 * @Description: 注释信息
 */
#include <sys/types.h>
#include <signal.h>
#include <bits/signum.h>

/// @brief 一个进程给其他进程发送信号的API是kill函数； 把信号sig发送给目标进程
/// @param pid 目标进程
///         pid > 0  信号发送给PID为pid的进程
///         pid = 0  信号发送给本进程组内的其他进程
///         pid = -1 信号发送给除init进程外的所有进程， 但发送需要拥有对目标进程发送信号的权限
///         pid < -1 信号发送给组ID为 -pid的进程组中所有成员
/// @param sig
///        linux信号值都大于0， 如果sig=0，则kill不发送任何信号；但sig设为0可以检测目标进程或进程组是否存在
/// @return 成功返回0，失败返回-1并设置errno
///     errno的类型：
///         EINVAL: 无效的信号
///         EPERM: 该进程没有权限发送信号给任何一个目标进程
///         ESRCH: 目标进程或进程组不存在
int kill(pid_t pid, int sig) {}

/// @brief 目标进程在收到信号时，需定义一个接收函数来处理之。
/// 信号处理函数的原型如下：
/// 信号处理函数只带有一个整型参数，该参数用来指示信号类型。
/// 信号处理函数应该是 可重入的，否则很容易引发 一些竞态条件。所以在信号处理函数中严禁调用一些不安全的 函数。
typedef void (*__sighandler_t)(int);

/**
 * 信号的默认处理方式：
 *      - 结束进程:Term
 *      - 忽略信号:Ign
 *      - 结束进程并生成核心转储文件:Core
 *      - 暂停进程:Stop
 *      - 继续进程:Cont
 */
#define SIG_DFL((__sighandler_t)0) // 忽略目标信号
#define SIG_IGN((__sighandler_t)1) // 使用信号的默认处理方式
