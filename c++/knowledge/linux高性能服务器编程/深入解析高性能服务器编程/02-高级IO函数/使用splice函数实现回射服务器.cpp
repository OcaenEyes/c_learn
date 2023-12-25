#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

/// @brief 通过splice 函数将客户端的内容读人到pipefd[1]中，然后再使用splice 函数从 pipcfd[0]中读出该内容到客户端，从而实现了简单高效的回射服务。整个过程未执行recv/ send 操作，因此也未涉及用户空间和内核空间之间的数据拷贝
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number \n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t clien_addrlen = sizeof(client);
    int connfd = accept(sock, (struct sockaddr *)&client, &clien_addrlen);

    if (connfd < 0)
    {
        printf("errno is: %d\n", errno);
    }
    else
    {
        int pipefd[2];
        assert(ret != -1);

        ret = pipe(pipefd); // 创建管道

        // 将connfd上流入的客户端数据 定向到管道
        ret = splice(connfd, NULL, pipefd[1],
                     NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);

        // 将管道的输出定向到connfd客户端连接文件描述符
        ret = splice(pipefd[0], NULL, connfd,
                     NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);

        close(connfd);
    }

    close(sock);
    return 0;
}