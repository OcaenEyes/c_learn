#pragma once

#include "noncopyable.h"

#include <functional>
#include <memory>

namespace ocean_muduo
{

    class eventloop; // 前置类型声明， 在源文件具体使用的地方，在引用头文件
    class timestamp; // 前置类型声明， 在源文件具体使用的地方，在引用头文件

    /**
     * @brief channel 理解为通道， 封装了sockfd和其感兴趣的event(譬如 EPOLLIN、EPOLLOUT事件)
     *                            还绑定了poller返回的具体事件
     *
     */
    class channel : public noncopyable
    {
    public:
        typedef std::function<void()> EventCallback;
        // using EventCallback = std::function<void()>;  //与上方 typedef等价 ，using更加直观

        using ReadEventCallback = std::function<void(timestamp)>;
        // typedef std::function<void(timestamp)> ReadEventCallback;  // 与上方using等价

        channel(eventloop *loop, int fd);
        ~channel();

        // fd得到Poller通知后，处理事件的。
        // 调用相应的回调方法
        void handle_event(timestamp receive_time);

        // 设置读事件回调函数对象
        void set_read_callback(const ReadEventCallback &cb) { read_callback_ = cb; }
        // 设置写事件回调函数对象
        void set_write_complete_callback_(const EventCallback &cb) { write_complete_callback_ = cb; }
        // 设置关闭事件回调函数对象
        void set_close_callback(const EventCallback &cb) { close_callback_ = cb; }
        // 设置错误事件回调函数对象
        void set_error_callback(const EventCallback &cb) { error_callback_ = cb; }

        // 防止当channel被手动remove掉， chanel还在执行回调操作
        void tie(const std::shared_ptr<void> &obj);

        // 返回fd_
        int fd() const { return fd_; }
        // 设置events_
        void set_events(int events) { events_ = events; }
        // 返回events_
        int events() const { return events_; }
        // 设置revents_
        void set_revents(int rev) { revents_ = rev; }
        // 返回revents_
        int revents() const { return revents_; }
        // 设置index_
        void set_index(int idx) { index_ = idx; }
        // 返回index_
        int index() const { return index_; }

        // 设置fd相应的事件状态
        // 开启读事件
        void enable_reading()
        {
            events_ |= k_read_event_;
            update();
        }
        // 开启写事件
        void enable_writing()
        {
            events_ |= k_write_event_;
            update();
        }
        // 关闭读事件
        void disable_reading()
        {
            events_ &= ~k_read_event_;
            update();
        }
        // 关闭写事件
        void disable_writing()
        {
            events_ &= ~k_write_event_;
            update();
        }
        // 关闭所有事件
        void disable_all()
        {
            events_ = k_none_event_;
            update();
        }

        // 返回当前fd是否没有注册感兴趣的事件
        bool is_none_event() const { return events_ == k_none_event_; }
        // 返回channel是否在监听读事件
        bool is_reading() const { return events_ & k_read_event_; }
        // 返回channel是否在监听写事件
        bool is_writing() const { return events_ & k_write_event_; }

        // 返回channel所属的eventloop [one loop per thread]
        eventloop *owner_loop() { return loop_; }
        // 设置channel所属的eventloop
        void set_owner_loop(eventloop *loop) { loop_ = loop; }

        // 移除channel
        void remove();

    private:
        static const int k_none_event_;
        static const int k_read_event_;
        static const int k_write_event_;

        eventloop *loop_; // 事件循环
        const int fd_;    // 文件描述符 ,Poller监听的对象
        int events_;      // 注册fd感兴趣的event
        int revents_;     // Poller返回的fd实际发生的事件
        int index_;       // 用于在poller中查找channel

        std::weak_ptr<void> tie_;
        bool tied_; // 是否绑定了对象

        // 因为channel通道里面能 获知fd最终发生的具体事件， 所以它负责进行
        ReadEventCallback read_callback_; // 读事件回调
        EventCallback write_complete_callback_;    // 写事件回调
        EventCallback close_callback_;    // 关闭事件回调
        EventCallback error_callback_;    // 错误事件回调

        // 更新channel的revents_
        void update();

        // 处理事件with guard
        void handle_event_with_guard(timestamp receive_time);
    };
   
    

} // namespace ocean_muduo
