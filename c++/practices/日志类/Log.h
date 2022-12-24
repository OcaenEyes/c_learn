/*
 * @Author: OCEAN.GZY
 * @Date: 2022-12-24 19:01:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-12-24 19:18:18
 * @FilePath: /c++/practices/日志类/Log.h
 * @Description: 注释信息
 */
#ifndef _LOG_H__
#define _LOG_H__

#include <iostream>

class Log
{
public:
    const int logLevelError = 0;
    const int logLevelWarn = 1;
    const int logLevelInfo = 2;

private:
    /* data */
    int _logLevel = logLevelInfo;

public:
    Log(/* args */);
    ~Log();
    void setLevel(int level);
    void warn(const char *message);
    void error(const char *message);
    void info(const char *message);
};

#endif