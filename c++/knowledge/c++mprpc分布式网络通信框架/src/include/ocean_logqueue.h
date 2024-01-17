/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-17 03:33:29
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-17 03:50:06
 * @FilePath: /c++/knowledge/c++mprpc分布式网络通信框架/src/include/ocean_logqueue.h
 * @Description: 注释信息
 */
#pragma once

#include <queue>
#include <thread>
#include <mutex>              // pthread_mutex_t
#include <condition_variable> // pthread_condition_t

// 异步写日志的 日志队列
template <typename T>
class LogQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;

public:
    LogQueue(/* args */) {}
    ~LogQueue() {}

    void Push(const T &data) // 对尾插入
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_cond.notify_one(); // 通知：日志队列进入了一个新的任务
    }

    T Pop() // 对头弹出
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            // 日志队列为空，线程进入wait状态
            m_cond.wait(lock);
        }

        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
};
