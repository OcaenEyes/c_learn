/*
 * @Author: OCEAN.GZY
 * @Date: 2022-12-24 19:10:59
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-12-24 19:12:25
 * @FilePath: /c++/practices/日志类/main.cpp
 * @Description: 注释信息
 */
#include "Log.h"

int main()
{
    Log _log;
    _log.setLevel(_log.logLevelError);
    _log.error("错误了！");
    return 0;
}