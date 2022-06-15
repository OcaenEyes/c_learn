#include "publisher.h"

int main(int argc, char *argv[])
{
    CRedisPublisher publisher;
    bool ret = publisher.init();

    if (!ret)
    {
        printf("初始化失败\n");
        return 0;
    }

    ret = publisher.connect();
    if (!ret)
    {
        printf("连接失败\n");
        return 0;
    }

    while (true)
    {
        printf(":开始向test-channel发布消息: \n");
        publisher.publish("test-channel", "Hello gzy");
        sleep(1);
    }

    publisher.disconnect();
    publisher.uninit();

    return 0;
}