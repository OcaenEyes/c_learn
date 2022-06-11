#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "../include/subscriber.h"

CRedisSubscriber::CRedisSubscriber() : _event_base(0), _event_thread(0), _redis_context(0) {}

CRedisSubscriber::~CRedisSubscriber() {}

bool CRedisSubscriber::init(const NotifyMessageFn &fn)
{
    //初始化事件
    _notify_message_fn = fn;
    _event_base = event_base_new();
    if (NULL == _event_base)
    {
        printf("创建redis事件失败 \n");
        return false;
    }

    memset(&_event_sem, 0, sizeof(_event_sem));
    int ret = sem_init(&_event_sem, 0, 0);
    if (ret != 0)
    {
        printf("初始化sem失败 \n");
        return false;
    }
    return true;
}

bool CRedisSubscriber::uninit()
{
    _event_base = NULL;
    sem_destroy(&_event_sem);
    return true;
}

bool CRedisSubscriber::connect()
{
    //连接 redis
    char redis_ip[] = "172.17.0.2";
    int redis_port = 6379;
    char redis_user_pass[] = "123456";
    _redis_context = redisAsyncConnect(redis_ip, redis_port);
    if (NULL == _redis_context)
    {
        printf("连接redis失败 \n");
        return false;
    }
    if (_redis_context->err)
    {
        printf("连接redis错误:%d,%s \n", _redis_context->err, _redis_context->errstr);
        return false;
    }

    // attach the event
    // 将事件绑定到redis context上，使设置给redis的回调跟事件关联
    redisLibeventAttach(_redis_context, _event_base);

    // 串讲事件处理线程
    int ret = pthread_create(&_event_thread, 0, &CRedisSubscriber::event_thread, this);

    if (ret != 0)
    {
        printf(": 创建事件线程失败 \n");
        disconnect();
        return false;
    }

    //设置回调
    redisAsyncSetConnectCallback(_redis_context, &CRedisSubscriber::connect_callback);

    redisAsyncSetDisconnectCallback(_redis_context, &CRedisSubscriber::disconnect_callback);

    redisAsyncCommand(_redis_context, NULL, NULL, "AUTH %s", redis_user_pass);

    // 启动事件线程
    sem_post(&_event_sem);

    return true;
}

bool CRedisSubscriber::disconnect()
{
    if (_redis_context)
    {
        redisAsyncDisconnect(_redis_context);
        redisAsyncFree(_redis_context);
        _redis_context == NULL;
    }
    return true;
}

bool CRedisSubscriber::subscribe(const string &channel_name)
{
    int ret = redisAsyncCommand(_redis_context, &CRedisSubscriber::command_callback, this, "SUBSCRIBE %s", channel_name.c_str());
    printf("订阅命令结果:%d\n", ret);
    if (REDIS_ERR == ret)
    {
        printf(": 订阅命令失败 %d \n", ret);
        return false;
    }
    printf(": 订阅命令成功 %s \n", channel_name.c_str());
    return true;
}

void CRedisSubscriber::connect_callback(const redisAsyncContext *redis_context, int status)
{
    if (status != REDIS_OK)
    {
        printf(":error: %s \n", redis_context->errstr);
    }
    else
    {
        printf(":redis连接成功");
    }
}

void CRedisSubscriber::disconnect_callback(const redisAsyncContext *redis_context, int status)
{
    if (status != REDIS_OK)
    {
        printf(":异常退出: %s \n", redis_context->errstr);
    }
}

void CRedisSubscriber::command_callback(redisAsyncContext *redis_context, void *reply, void *privdata)
{
    if (NULL == reply || NULL == privdata)
    {
        printf("订阅reply ：%s", reply);
        printf("订阅privdata ： %s", privdata);
        return;
    }
    // 静态函数中，要使用类的成员变量，把当前的this指针传进来，用this指针间接访问
    CRedisSubscriber *self_this = reinterpret_cast<CRedisSubscriber *>(privdata);
    redisReply *redis_reply = reinterpret_cast<redisReply *>(reply);

    printf("接收到的消息replay type：%d \n", redis_reply->type);
    printf("接收到的消息replay elements：%d \n", redis_reply->elements);
    printf("接收到的消息replay element：%s \n", redis_reply->element);

    // 订阅接收到的消息， 是一个带三元素的数组
    if (redis_reply->type == REDIS_REPLY_ARRAY && redis_reply->elements == 3)
    {
        printf("接收到的消息是：%s：%d：%s：%d：%s：%d \n",
               redis_reply->element[0]->str, redis_reply->element[0]->len,
               redis_reply->element[1]->str, redis_reply->element[1]->len,
               redis_reply->element[2]->str, redis_reply->element[2]->len);

        // 调用函数对象把消息通知给外层
        self_this->_notify_message_fn(redis_reply->element[1]->str, redis_reply->element[2]->str, redis_reply->element[3]->len);
    }
}

void *CRedisSubscriber::event_thread(void *data)
{
    if (NULL == data)
    {
        printf(":Error! \n");
        assert(false);
        return NULL;
    }

    CRedisSubscriber *self_this = reinterpret_cast<CRedisSubscriber *>(data);
    return self_this->event_proc();
}

void *CRedisSubscriber::event_proc()
{
    sem_wait(&_event_sem);

    // 开启事件分发，event_base_dispatch会阻塞
    event_base_dispatch(_event_base);

    return NULL;
}
