/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-02 07:29:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-02 09:25:10
 * @FilePath: /c++/knowledge/c++线程池/v0.2/threadpool.cpp
 * @Description: 重构后的线程池实现
 */
#include "threadpool.hpp"

int Thread::generate_id_ = 0; // 静态成员变量需要在类外初始化
