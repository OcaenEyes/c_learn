#pragma once

#include "noncopyable.h"

#include <vector>
#include <unordered_map>

namespace ocean_muduo
{
    class eventloop; // 前置类型声明
    class channel;   // 前置类型声明
    class timestamp; // 前置类型声明

    // 抽象类 不能被实例化
    class poller : public noncopyable
    {

    public:
        using channels = std::vector<channel *>;

        // 构造函数
        poller(eventloop *loop);
        // 虚析构函数
        virtual ~poller();

        // 给所有IO复用 保留统一的接口
        virtual timestamp poll(int timeout_ms, channels *active_channels) = 0; // 轮询I/O事件
        virtual void update_channel(channel *chanl) = 0;                       // 更新channel
        virtual void remove_channel(channel *chanl) = 0;                       // 删除channel

        bool has_channel(channel *chanl) const; // 判断channel是否在poller中
        // eventloop 可以通过该接口，获取默认的IO复用的具体实现
        static poller *new_default_poller(eventloop *loop); // 创建默认的poller

    protected:
        // 定义一个map，用于存储key:sockfd 和 value:channel通道类型
        using channelmap = std::unordered_map<int, channel *>;
        channelmap channel_map_;

    private:
        eventloop *loop_; // 定义poller所属的事件循环eventloop
    };

} // namespace ocean_muduo
