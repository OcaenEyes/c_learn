#include <hiredis/hiredis.h>
#include <iostream>
#include <string>


int main(int argc, char **argv)

{
    redisContext *predisContext;
    redisReply *authReplay;
    redisReply *predisInfoReplay;

    char *hostname = argv[1];
    int port = atoi(argv[2]);
    char *pass = argv[3];

    struct timeval timeout = {2, 0}; // 2s的超时时间
    predisContext = redisConnectWithTimeout(hostname, port, timeout);
    if (predisContext == NULL || predisContext->err)
    {
        if (predisContext)
        {
            std::cout << "Connection error:" << predisContext->errstr << std::endl;
            std::cout << predisContext << std::endl;
            redisFree(predisContext);
        }
        else
        {
            std::cout << "Connection error: can't allocate redis context" << std::endl;
        }
        return -1;
    }

    authReplay = (redisReply *)redisCommand(predisContext, "AUTH %s", pass);
    if (authReplay->type == REDIS_REPLY_ERROR)
    {
        std::cout << "connect" << std::endl;
        std::cout << "connect type:" << authReplay->type << std::endl;
    }
    freeReplyObject(authReplay);

    // redisReply 是redis命令回复对象， redis返回的信息保存在reidsReplay对象中

    predisInfoReplay = (redisReply *)redisCommand(predisContext, "INFO");

    std::cout << "info" << std::endl;
    std::cout << "info" << predisInfoReplay->str << std::endl;

    freeReplyObject(predisInfoReplay);

    return 0;
}