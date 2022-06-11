#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "../include/publisher.h"

CRedisPublisher::CRedisPublisher() : _event_base(0), _event_thread(0),
                                     _redis_context(0) {}

CRedisPublisher::~CRedisPublisher() {}

bool CRedisPublisher::init()
{
    //初始化event
    _event_base = event_base_new();
    if (NULL == _event_base)
    {
        printf(": create redis event failed.\n");
        return false;
    }
    memset(&_event_sem, 0, sizeof(_event_sem));
    int ret = sem_init(&_event_sem, 0, 0);
    if (ret != 0)
    {
        printf(": Init sem failed. \n");
        return false;
    }
    return true;
}
bool CRedisPublisher::uninit()
{
    _event_base = NULL;
    sem_destroy(&_event_sem);
    return true;
}

bool CRedisPublisher::connect()
{
    // 连接redis
    _redis_context = redisAsyncConnect("172.0.0.2", 6379);
    if (/* condition */ NULL == _redis_context)
    {
        printf(": connect redis failed. \n");
        return false;
    }
    if (_redis_context->err)
    {
        printf(": connect redis error:%d, %s. \n", _redis_context->err, _redis_context->errstr);
        return false;
    }

    // 将事件绑定到redis context上，使设置给redis的回调跟事件关联
    redisLibeventAttach(_redis_context, _event_base);
    // 设置连接回调，当异步调用连接后，服务器处理连接请求结束后调用，通知调用者连接的状态
    redisAsyncSetConnectCallback(_redis_context, CRedisPublisher::connect_callback);
    // 设置断开连接回调，当服务器断开连接后，通知调用者连接断开，调用者可以利用这个函数实现重连
    redisAsyncSetDisconnectCallback(_redis_context, CRedisPublisher::disconnect_callback);
    char redis_user_pass[] = "123456";
    redisAsyncCommand(_redis_context, NULL, NULL, "AUTH %s", redis_user_pass);

    // 创建事件处理线程
    int ret = pthread_create(&_event_thread, 0, &CRedisPublisher::event_thread, this);
    if (ret != 0)
    {
        printf(":create event thread failed. \n");
        disconnect();
        return false;
    }

    // 启动事件线程
    sem_post(&_event_sem);
    return true;
}
bool CRedisPublisher::disconnect()
{
    if (_redis_context)
    {
        redisAsyncDisconnect(_redis_context);
        redisAsyncFree(_redis_context);
        _redis_context = NULL;
    }
    printf("已断开链接\n");
    return true;
}

bool CRedisPublisher::publish(const std::string &channel_name, const std::string &message)
{
    int ret = redisAsyncCommand(_redis_context,
                                &CRedisPublisher::command_callback, this, "PUBLISH %s %s",
                                channel_name.c_str(), message.c_str());
    printf("发布消息结果:%d\n", ret);
    printf("发布消息的内容:%s %s\n", channel_name.c_str(), message.c_str());
    if (REDIS_ERR == ret)
    {
        printf("Publish command failed: %d\n", ret);
        return false;
    }
    return true;
}

void CRedisPublisher::connect_callback(const redisAsyncContext *redis_context, int status)
{
    if (status != REDIS_OK)
    {
        printf(":redis connect error %s \n", redis_context->errstr);
    }
    else
    {
        printf(":redis connected! \n");
    }
}

void CRedisPublisher::disconnect_callback(const redisAsyncContext *redis_context, int status)
{
    if (status != REDIS_OK)
    {
        // 异常退出
        printf(":error: %s \n", redis_context->errstr);
    }
}

void CRedisPublisher::command_callback(redisAsyncContext *redis_context, void *reply, void *privdata)
{
    printf("command callback. \n");
}

void *CRedisPublisher::event_thread(void *data)
{
    if (NULL == data)
    {
        printf(":Error! \n");
        assert(false);
        return NULL;
    }

    CRedisPublisher *self_this = reinterpret_cast<CRedisPublisher *>(data);
    return self_this->event_proc();
}

void *CRedisPublisher::event_proc()
{
    sem_wait(&_event_sem);

    // 开启时间分发， event_base_dispatch会阻塞
    event_base_dispatch(_event_base);
    return NULL;
}