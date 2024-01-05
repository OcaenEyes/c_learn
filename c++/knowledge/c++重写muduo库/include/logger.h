#pragma once

#include "noncopyable.h"

#include <string>

namespace ocean_muduo
{
// 定义LOG_INFO宏
#define LOG_INFO(logformat, ...)                              \
    do                                                        \
    {                                                         \
        logger &loger__ = logger::instance();                 \
        logger__.set_level(logger_level::INFO);               \
        char buf[1024] = {0};                                 \
        snprintf(buf, sizeof(buf), logformat, ##__VA_ARGS__); \
        logger__.log(buf);                                    \
    } while (0)

    // 定义LOG_ERROR宏
#define LOG_ERROR(logformat, ...)                             \
    do                                                        \
    {                                                         \
        logger &loger__ = logger::instance();                 \
        logger__.set_level(logger_level::INFO);               \
        char buf[1024] = {0};                                 \
        snprintf(buf, sizeof(buf), logformat, ##__VA_ARGS__); \
        logger__.log(buf);                                    \
    } while (0)

    // 定义LOG_FATAL宏
#define LOG_FATAL(logformat, ...)                             \
    do                                                        \
    {                                                         \
        logger &loger__ = logger::instance();                 \
        logger__.set_level(logger_level::INFO);               \
        char buf[1024] = {0};                                 \
        snprintf(buf, sizeof(buf), logformat, ##__VA_ARGS__); \
        logger__.log(buf);                                    \
    } while (0)

#ifdef MUDEBUG
    // 定义LOG_DEBUG宏
#define LOG_DEBUG(logformat, ...)                             \
    do                                                        \
    {                                                         \
        logger &loger__ = logger::instance();                 \
        logger__.set_level(logger_level::INFO);               \
        char buf[1024] = {0};                                 \
        snprintf(buf, sizeof(buf), logformat, ##__VA_ARGS__); \
        logger__.log(buf);                                    \
    } while (0)
#else
    // 定义LOG_DEBUG宏
#define LOG_DEBUG(logformat, ...)
#endif

    /**
     * @brief 日志格式
     */
    struct log_format
    {
        std::string level;
        std::string time;
        std::string thread;
        std::string file;
        int line;
        std::string func;
        std::string content;
    };

    /**
     * @brief 日志级别：INFO信息、ERROR错误、FATAL致命、DEBUG调试
     */
    enum log_level
    {
        INFO,  // 普通
        ERROR, // 错误
        FATAL, // 致命
        DEBUG, // 调试
    };

    /**
     * @brief 日志类， 单例模式实现
     */
    class logger : public noncopyable
    {
    private:
        // 构造函数私有化
        logger(/* args */);
        // 析构函数私有化
        ~logger();

        // 私有成员变量，日志级别
        int log_level_;

    public:
        // 静态成员函数,用于获取logger单例对象
        static logger &instance();
        // 设置日志级别
        void set_log_level(int level);
        // 写日志
        void log(const std::string &msg);
    };

} // namespace ocean_muduo
