/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-06 15:23:47
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-07 03:26:18
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/06-信号/信号函数.cpp
 * @Description: 信号函数
 */
#include <signal.h>

/// @brief 为一个信号设置处理函数，使用signal系统调用
/// @param sig 指出要捕获的信号类型
/// @param _handler 是__sighandler_t类型的指针，用于指定信号sig的处理函数
/// @return 成功时返回一个函数指针，这个返回值是前一次调用signal函数时传入的函数指针【或者是信号sig对应的默认处理函数指针SIG_DEF--第一次调用signal】； 出错返回SIG_ERR，并设置errno
__sighandler_t signal(int sig, __sighandler_t _handler) {}

/// @brief 设置信号处理函数 【sigaction系统调用】
/// @param sig 指出要捕获的信号类型
/// @param act 指定新的信号处理方式
/// @param oact 输出信号先前的处理方式（如果不为NULL）
/// @return 
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact) {}

