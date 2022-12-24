/*
 * @Author: OCEAN.GZY
 * @Date: 2022-12-24 19:03:28
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-12-24 19:19:48
 * @FilePath: /c++/practices/日志类/Log.cpp
 * @Description: 注释信息
 */
#include "Log.h"

void Log::setLevel(int level)
{
    _logLevel = level;
}

void Log::warn(const char *message)
{
    if (_logLevel >= logLevelWarn)
        std ::cout << "[WARNING]" << message << std::endl;
}

void Log::error(const char *message)
{
    if (_logLevel >= logLevelError)
        std ::cout << "[ERROR]" << message << std::endl;
}

void Log::info(const char *message)
{
    if (_logLevel >= logLevelInfo)
        std ::cout << "[INFO]" << message << std::endl;
}
Log::Log(/* args */)
{
}

Log::~Log()
{
}