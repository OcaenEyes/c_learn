/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-07 03:32:20
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-07 07:07:08
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/06-信号/信号集.cpp
 * @Description: 注释信息
 */

#include <signal.h>

/**
 * 设置、修改、删除、查询信号集
 */
int sigemptyset(sigset_t *_set) {}                   // 清空信号集
int sigfillset(sigset_t *_set) {}                    // 在信号集中设置所有信号
int sigaddset(sigset_t *_set, int _signo) {}         // 将信号_signo添加到信号集中
int sigdelset(sigset_t *_set, int _signo) {}         // 将信号_signo从信号集中移除
int sigismember(const sigset_t *_set, int _signo) {} // 测试_signo是否在信号集中

/// @brief 设置或查看进程的信号掩码
/// @param _how 如果_set不为NUL，则_how指定设置进程信号掩码的方式
///         SIG_BLOCK   新的进程信号掩码是其当前值 和_set指定信号集的并集
///         SIG_UNBLOCK 新的进程信号掩码是期当前值 和~_set信号集的交集， 因为_set指定的信号集将不被屏蔽
///         SIG_SETMASK  直接将进程信号掩码设置为_set
/// @param _set  指定新的信号掩码; 如果_set为NULL，则进程信号掩码不变，仍可使用_oset来获得当前的信号掩码
/// @param _oset 输出原来的信号掩码(如果不为NULL)
/// @return 成功返回0 ，失败返回-1并设置errno
int sigprocmasdk(int _how, const sigset_t *_set, sigset_t *_oset) {}

/// @brief 获得进程当前被挂起的信号集
/// @param set
/// @return
int sigpending(sigset_t *set) {}