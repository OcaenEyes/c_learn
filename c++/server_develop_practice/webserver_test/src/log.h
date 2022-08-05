/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-05 07:40:54
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-05 11:45:30
 * @FilePath: /c++/server_develop_practice/webserver_test/src/log.h
 * @Description: 注释信息
 */
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdarg.h>
#include <pthread.h>
#include "block_queue.h"

class log
{
private:
    char dir_name[128]; // 路径名
    char log_name[128]; // log文件名称
    int m_split_lines;  //日志最大行数
    int m_log_buf_size; //日志缓冲区大小
    long long m_count;  //日志行数记录
    int m_today;        //按天分类
    FILE *m_fp;         // 打开log的文件指针
    char *m_buf;
    block_queue<std::string> *m_log_queue; //阻塞队列
    bool m_is_async;                       // 是否同步标志位
    locker m_mutex;
    int m_close_log; //关闭日志

private:
    log();
    virtual ~log();
    void *async_write_log()
    {
        std::string single_log;
        // 从阻塞线程中取出一个日志string 写入文件
        while (m_log_queue->pop(single_log))
        {
            m_mutex.lock();
            fputs(single_log.c_str(), m_fp);
            m_mutex.unlock();
        }
    }

public:
    static log *get_instance()
    {
        static log initstate;
        return &initstate;
    }

    static void *flush_log_thread(void *args)
    {
        log::get_instance()->async_write_log();
    }
    //可选的参数有 日志文件、日志缓冲区大小、最大行数、及最长日志队列
    bool init(const char *file_name, int close_log, int log_buf_size = 8192, int split_lines = 500000, int max_queue_size = 0);
    void write_log(int level, const char *format, ...);
    void flush(void);

    log(/* args */);
    ~log();
};

#define LOG_DEBUG(format, ...)                                    \
    if (0 == m_close_log)                                         \
    {                                                             \
        log::get_instance()->write_log(0, format, ##__VA_ARGS__); \
        log::get_instance()->flush();                             \
    }
#define LOG_INFO(format, ...)                                     \
    if (0 == m_close_log)                                         \
    {                                                             \
        log::get_instance()->write_log(1, format, ##__VA_ARGS__); \
        log::get_instance()->flush();                             \
    }
#define LOG_WARN(format, ...)                                     \
    if (0 == m_close_log)                                         \
    {                                                             \
        log::get_instance()->write_log(2, format, ##__VA_ARGS__); \
        log::get_instance()->flush();                             \
    }
#define LOG_ERROR(format, ...)                                    \
    if (0 == m_close_log)                                         \
    {                                                             \
        log::get_instance()->write_log(3, format, ##__VA_ARGS__); \
        log::get_instance()->flush();                             \
    }
#endif