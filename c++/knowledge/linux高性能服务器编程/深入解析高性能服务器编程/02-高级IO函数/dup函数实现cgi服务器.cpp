#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    /*bzero() 能够将内存块（字符串）的前n个字节清零，在"string.h"头文件中，
            原型为：void bzero(void *s, int n);
            【参数】s为内存（字符串）指针，n 为需要清零的字节数。
            bzero()将参数s 所指的内存区域前n 个字节全部设为零。
    */
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;

    inet_pton(AF_INET, ip, &address.sin_addr); // 将标准文本表示形式的IPv4或IPv6 Internet网络地址转换为数字二进制形式
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret = -1);

    struct sockaddr_in client;
    socklen_t client_addrlen = sizeof(client);
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlen);
    if (connfd < 0)
    {
        printf("errno is : %d\n", errno);
    }
    else
    {
        close(STDOUT_FILENO); // 先关闭标准文件描述符 STDOUT_FILENO(值为1)
        dup(connfd); // 复制socket文件描述符connfd， 因为dup总是返回系统中最小的可用文件描述符，所以实际返回值是1【即之前关闭的标准输出文件描述符的值】
        printf("abcd\n");// 服务器输出到标准输出的内容“abcd”，就会直接发送到与客户端连接对应socket上，因此printf调用的输出将被客户端获得【不是显示在服务器程序的终端上】--->>这就是cgi服务器的基础工作原理
        close(connfd);
    }

    close(sock);
    return 0;
}