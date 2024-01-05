#include "logger.h"
#include "timestamp.h"

#include <iostream>

namespace ocean_muduo
{
    logger::logger()
    {
    }

    logger::~logger() {}

    // 静态成员函数,用于获取logger单例对象
    logger &logger::instance()
    {
        static logger logger_;
        return logger_;
    }

    // 设置日志级别
    void logger::set_log_level(int level)
    {
        log_level_ = level;
    }

    // 写日志
    // [级别信息][time][message]
    void logger::log(const std::string &msg)
    {
        switch (log_level_)
        {
        case INFO:
            std::cout << "[INFO][" << timestamp::now().to_string() << "]" << msg << "\n";
            break;

        case ERROR:
            std::cout << "[ERROR][" << timestamp::now().to_string() << "]" << msg << "\n";
            break;
        case FATAL:
            std::cout << "[FATAL][" << timestamp::now().to_string() << "]" << msg << "\n";
            break;
        case DEBUG:
            std::cout << "[DEBUG][" << timestamp::now().to_string() << "]" << msg << "\n";
            break;
        default:
            std::cout << "[INFO][" << timestamp::now().to_string() << "]" << msg << "\n";
            break;
            break;
        }
    }

} // namespace name
