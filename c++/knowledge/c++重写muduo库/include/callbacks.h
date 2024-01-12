/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-11 08:57:06
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-11 14:41:21
 * @FilePath: /c++/knowledge/c++重写muduo库/include/callbacks.h
 * @Description: 注释信息
 */
#pragma once

#include <memory>
#include <functional>

namespace ocean_muduo
{
    class buffer;
    class tcpconnection;
    class timestamp;

    using TcpConnectionPtr = std::shared_ptr<tcpconnection>;
    using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
    using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
    using WriteCompleteCallback = std::function<void(const TcpConnectionPtr &)>;

    using MessageCallback = std::function<void(const TcpConnectionPtr &, buffer *, timestamp)>;


    using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr&, size_t)>;

} // namespace ocean_muduo
