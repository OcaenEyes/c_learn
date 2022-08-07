#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <stdlib.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <boost/functional.hpp>

using namespace std;

class CRedisSubscriber
{
public:
    typedef function<void(const char *, const char *, int)> NotifyMessageFn;
    CRedisSubscriber();
    ~CRedisSubscriber();

    bool init(const NotifyMessageFn &fn);
    bool uninit();
    bool connect();
    bool disconnect();

    bool subscribe(const string &channel_name);

private:
    // 下面三个回调函数供redis服务调用
    // 连接回调
    static void connect_callback(const redisAsyncContext *redis_context, int status);

    // 断开连接的回调
    static void disconnect_callback(const redisAsyncContext *redis_context, int status);

    // 执行命令回调
    static void command_callback(redisAsyncContext *redis_context, void *reply, void *privdata);

    // 事件分发线程函数
    static void *event_thread(void *data);
    void *event_proc();

private:
    // libevent事件对象
    event_base *_event_base;
    // 事件线程ID
    pthread_t _event_thread;
    // 事件线程的信号量
    sem_t _event_sem;
    // hiredis异步对象
    redisAsyncContext *_redis_context;

    // 通知外层的回调函数对象
    NotifyMessageFn _notify_message_fn;
};

#endif