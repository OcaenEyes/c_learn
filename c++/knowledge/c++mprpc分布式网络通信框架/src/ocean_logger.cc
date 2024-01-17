/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 02:45:37
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 06:27:10
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/ocean_logger.cc
 * @Description: 注释信息
 */
#include "ocean_logger.h"

#include <time.h>
#include <iostream>
#include <functional>

void Logger::Task()
{
    while (true)
    {
        // 获取当前的日期， 然后取日志信息，写入对应的文件中
        time_t now = time(nullptr);
        tm *now_tm = localtime(&now); // 年需要+1900, 月需要+1

        char file_name[128];
        sprintf(file_name, "%d-%d-%d-log.txt", now_tm->tm_year + 1900, now_tm->tm_mon + 1, now_tm->tm_mday);

        FILE *pf = fopen(file_name, "a+");
        if (pf == nullptr)
        {
            std::cout << "log file: " << file_name << "open error!\n";
            exit(EXIT_FAILURE);
        }
        std::string msg = m_log_queue.Pop();

        char time_buf[128];
        sprintf(time_buf, "%d-%d-%d =>[%s] ",
                now_tm->tm_hour,
                now_tm->tm_min,
                now_tm->tm_sec,
                m_log_level == INFO ? "INFO" : "ERROR"); // 每行日志的时分秒

        msg.insert(0, time_buf); // 在日志msg前面插入时分秒

        msg.append("\n"); // 在末尾增加换行符

        fputs(msg.c_str(), pf);
        fclose(pf);
    }
}

// 构造函数
Logger::Logger()
{
    // 启动专门的写日志线程
    std::thread write_log_task(std::bind(&Logger::Task, this));
    // 设置分离线程
    write_log_task.detach();
}

Logger::~Logger()
{
}

// 获取日志单例
Logger &Logger::GetInstance()
{
    static Logger loger;
    return loger;
}

LogQueue<std::string> &Logger::GetLogQueue()
{
    return m_log_queue;
}

void Logger::SetLogLevel(LogLevel level)
{
    m_log_level = level;
}

// 写日志， 把日志信息 写入lockqueue缓冲区当中
void Logger::Log(std::string msg)
{
    m_log_queue.Push(msg);
}
