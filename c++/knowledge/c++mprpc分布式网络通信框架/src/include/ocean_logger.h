/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 02:35:15
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 06:03:41
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/ocean_logger.h
 * @Description: 注释信息
 */
#pragma once

#include "ocean_logqueue.h"

// OCEANMprpc框架提供的日志系统
enum LogLevel
{
    INFO,  // 普通信息
    ERROR, // 错误信息
};

// 单例模式
class Logger
{
private:
    int m_log_level;                   // 记录日志级别
    LogQueue<std::string> m_log_queue; // 日志缓冲队列

    Logger(/* args */);
    ~Logger();

    Logger(const Logger &) = delete;            // 禁用拷贝构造
    Logger(Logger &&) = delete;                 // 禁用拷贝构造
    Logger &operator=(const Logger &) = delete; // 禁用赋值操作

    void Task();

public:
    void SetLogLevel(LogLevel level); // 设置日志级别
    void Log(std::string msg);        // 写日志
    static Logger &GetInstance();     // 获取日志的单例
    LogQueue<std::string> &GetLogQueue();
};

// 定义日志宏
#define LOG_INFO(logmsgformat, ...)                     \
    do                                                  \
    {                                                   \
        Logger &loger = Logger::GetInstance();          \
        loger.SetLogLevel(INFO);                        \
        char c[1024] = {0};                             \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        loger.Log(c);                                   \
    } while (0);
#define LOG_ERROR(logmsgformat, ...)                    \
    do                                                  \
    {                                                   \
        Logger &loger = Logger::GetInstance();          \
        loger.SetLogLevel(ERROR);                       \
        char c[1024] = {0};                             \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        loger.Log(c);                                   \
    } while (0);