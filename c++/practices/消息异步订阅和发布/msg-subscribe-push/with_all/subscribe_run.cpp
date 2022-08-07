#include "subscriber.h"

void receive_message(const char *channel_name, const char *message, int len)
{
    printf("收到消息：\n channel_name: %s \n message: %s \n", channel_name, message);
}

int main(int argc, char *argv[])
{
    CRedisSubscriber subcriber;
    CRedisSubscriber::NotifyMessageFn fn = bind(receive_message, std::placeholders::_1,
                                                std::placeholders::_2, std::placeholders::_3);

    bool ret = subcriber.init(fn);
    if (!ret)
    {
        printf("初始化失败\n");
        return 0;
    }

    ret = subcriber.connect();
    if (!ret)
    {
        printf("连接失败\n");
        return 0;
    }

    subcriber.subscribe("test-channel");
    while (true)
    {
        sleep(1);
    }

    subcriber.disconnect();
    subcriber.uninit();

    return 0;
}