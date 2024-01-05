#pragma once

#include "noncopyable.h"

#include <string>

namespace ocean_muduo
{
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
        int level_;

    public:
        // 静态成员函数,用于获取logger单例对象
        static logger *instance();
        // 设置日志级别
        void set_log_level(int level);
        // 写日志
        void log(const std::string &msg);
        // 写ERROR日志
        void error(const std::string &msg);
        // 写FATAL日志
        void fatal(const std::string &msg);
        // 写DEBUG日志
        void debug(const std::string &msg);
    };

    logger::logger(/* args */)
    {
    }
    logger::~logger(/* args */)
    {
    }

} // namespace ocean_muduo
