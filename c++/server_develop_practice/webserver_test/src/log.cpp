/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-05 08:29:28
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-05 12:17:22
 * @FilePath: /c++/server_develop_practice/webserver_test/src/log.cpp
 * @Description: 注释信息
 */
#include "log.h"

log::log(/* args */)
{
    m_count = 0;
    m_is_async = false;
}

log::~log()
{
    if (m_fp != NULL)
    {
        fclose(m_fp);
    }
}

// 异步需要设置阻塞队列的长度， 同步不需要设置
bool log::init(const char *file_name, int close_log, int log_buf_size, int split_lines, int max_queue_size)
{
    // 如果设置了max_queue_size 则为异步
    if (max_queue_size >= 1)
    {
        m_is_async = true;
        m_log_queue = new block_queue<std::string>(max_queue_size);
        pthread_t tid;

        // flush_log_thread回调函数，表示创建异步线程写日志
        pthread_create(&tid, NULL, flush_log_thread, NULL);
    }

    m_close_log = close_log;
    m_log_buf_size = log_buf_size;
    m_buf = new char[m_log_buf_size];
    memset(m_buf, '\0', m_log_buf_size);
    m_split_lines = split_lines;

    time_t t = time(NULL);
    struct tm *sys_tem = localtime(&t);
    struct tm my_tm = *sys_tem;

    const char *p = strrchr(file_name, '/');
    char log_full_name[256] = {0};

    if (p == NULL)
    {
        snprintf(log_full_name, 255, "%d_%02d_%02d_%s", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, file_name);
    }
    else
    {
        strcpy(log_name, p + 1);
        strncpy(dir_name, file_name, p - file_name + 1);
        snprintf(log_full_name, 255, "%s%d_%02d_%02d_%s", dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, file_name);
    }

    m_today = my_tm.tm_mday;

    m_fp = fopen(log_full_name, "a");
    if (m_fp == NULL)
    {
        return false;
    }
    return true;
}

void log::write_log(int level, const char *format, ...)
{
    struct timeval now = {0, 0};
    gettimeofday(&now, NULL);
    time_t t = now.tv_sec;
    struct tm *sys_tem = localtime(&t);
    struct tm my_tm = *sys_tem;
    char s[16] = {0};
    switch (level)
    {
    case 0:
        strcpy(s, "[debug]:");
        break;
    case 1:
        strcpy(s, "[info]:");
        break;
    case 2:
        strcpy(s, "[warn]:");
        break;
    case 3:
        strcpy(s, "[error]:");
        break;
    default:
        strcpy(s, "[info]:");
        break;
    }

    // 写入一个log，对m_count ++ , m_split_lines最大行数
    m_mutex.lock();
    m_count ++;
    
}

void log::flush(void)
{
    m_mutex.lock();
    //强制刷新写入流缓冲区
    fflush(m_fp);
    m_mutex.unlock();
}