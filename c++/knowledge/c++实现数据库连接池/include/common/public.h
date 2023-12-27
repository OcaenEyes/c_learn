#pragma once
#include <iostream>
#define LOG(str)                                                                                        \
    do                                                                                                  \
    {                                                                                                   \
        std::cout << __FILE__ << ": " << __LINE__ << ": " << __TIMESTAMP__ << ": " << str << std::endl; \
    } while (0)

#define LOG_ERROR(str)                                                                                               \
    do                                                                                                               \
    {                                                                                                                \
        std::cerr << "[ERROR]" << __FILE__ << ": " << __LINE__ << ": " << __TIMESTAMP__ << ": " << str << std::endl; \
    } while (0)

#define LOG_WARNING(str)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        std::cerr << "[WARNING]" << __FILE__ << ": " << __LINE__ << ": " << __TIMESTAMP__ << ": " << str << std::endl; \
    } while (0)

#define LOG_INFO(str)                                                                                               \
    do                                                                                                              \
    {                                                                                                               \
        std::cout << "[INFO]" << __FILE__ << ": " << __LINE__ << ": " << __TIMESTAMP__ << ": " << str << std::endl; \
    } while (0)

#define LOG_DEBUG(str)                                                                                               \
    do                                                                                                               \
    {                                                                                                                \
        std::cout << "[DEBUG]" << __FILE__ << ": " << __LINE__ << ": " << __TIMESTAMP__ << ": " << str << std::endl; \
    } while (0)
