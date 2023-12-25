/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-06 08:48:14
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-06 09:16:08
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/05-IO复用/IO复用-高级应用/聊天室程序/client.cpp
 * @Description: 聊天室客户端
 *
 *  客户端程序使用epoll同时监听用户输入和网络连接， 并利用splice函数将用户输入内容，直接定向到网络连接以发送， 从而实现数据零拷贝
 */

#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("应用程序:%s需要输入IP地址 Port端口号参数\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("连接失败\n");
        close(sockfd);
        return 1;
    }

    pollfd fds[2];
    // 注册文件描述符0（标准输入）和文件描述符sockfd上的可读事件
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;

    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe(pipefd);
    assert(ret != -1);

    while (1)
    {
        ret = poll(fds, 2, -1);
        if (ret < 0)
        {
            printf("poll失败\n");
            break;
        }

        if (fds[1].revents & POLLRDHUP)
        {
            printf("服务器关闭了连接\n");
            break;
        }
        else if (fds[1].revents & POLLIN)
        {
            memset(read_buf, '\0', BUFFER_SIZE);
            recv(fds[1].fd, read_buf, BUFFER_SIZE, 0);
            printf("%s\n", read_buf);
        }

        if (fds[0].revents & POLLIN)
        {
            // 使用splice将用户输入的数据直接写到sockfd上（0拷贝）
            ret = splice(0, NULL, pipefd[1], NULL, 32768,
                         SPLICE_F_MORE | SPLICE_F_MOVE);
            ret = splice(pipefd[0], NULL, sockfd, NULL, 32768,
                         SPLICE_F_MORE | SPLICE_F_MOVE);
        }
    }

    close(sockfd);
    return 0;
}