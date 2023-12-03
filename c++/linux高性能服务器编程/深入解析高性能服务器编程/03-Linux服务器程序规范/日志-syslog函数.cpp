/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 19:00:08
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 19:08:19
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/03-Linux服务器程序规范/syslog函数.cpp
 * @Description: 注释信息
 */
#include <syslog.h>

/**
 * @description: 使用syslog函数与rsyslogd守护进程通信
 * @param {int} priority
 * @param {char*} message
 * @return {*}
 */
void syslog(int priority, const char *message, ...) {}

/**
 * @description: 改变默认输出方式
 * @param {const char*} ident 指定的字符串将 添加到日志消息的日期和时间之后， 通常被设置为程序的名字
 * @param {int} logopt 对syslog的行为配置
 *          - #define LOG_PID   0x01     // 在日志消息中包含程序PID
 *          - #define LOG_CONS  0x02    // 如果消息不能记录到日志文件，则打印至终端
 *          - #define LOG_ODELAY    0x04    // 延迟打开日志功能，知道第一次调用syslog
 *          - #define LOG_NDELAY    0x08    // 不延迟打开日志功能
 * @param {int} facility 修改syslog函数中的默认设置
 * @return {*}
 */
void openlog(const char *ident, int logopt, int facility) {}


/**
 * @description: 日志过滤，设置日志掩码，使日志级别大于日志掩码的日志信息被系统忽略
 * @param {int} maskpri 日志掩码值
 * @return {*}
 */
int setlogmask(int maskpri){}

/**
 * @description: 关闭日志功能
 * @return {*}
 */
void closelog(){}