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
    using WriteCallback = std::function<void(const TcpConnectionPtr &)>;

    using MessageCallback = std::function<void(const TcpConnectionPtr &, buffer *, timestamp)>;

} // namespace ocean_muduo
