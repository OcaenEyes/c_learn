/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-06 08:47:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-06 11:31:21
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/05-IO复用/IO复用-高级应用/聊天室程序/server.cpp
 * @Description: 聊天室服务器端
 *
 *  使用poll同时管理 监听socket 和连接soccer， 并且使用牺牲空间换时间的策略来提高服务器性能
 *
 */

#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>

#define USER_LIMIT 20  // 最大用户数量
#define BUFFER_SIZE 64 // 读缓冲区大小
#define FD_LIMIT 65535 // 文件描述符数量限制

// 客户数据：客户端socket地址、待写到客户端的数据位置、从客户端读入的数据
struct client_data
{
    sockaddr_in address;
    char *write_buf;
    char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("服务器程序:%s需要输入IP地址 Port端口号参数\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 20);
    assert(ret != -1);

    /**
     * 创建users数组， 分配FD_LIMIT个client_data对象
     *  -- 每个可能的socket连接都可以获得一个client_data对象，
     *  -- 并且socket的值可以直接用来索引（作为数组的下标） socket连接对应的client_data --> 这是将socket和客户数据进行关联的简单而高效的方式
     */
    client_data *users = new client_data[FD_LIMIT];
    // 尽管分配了足够多的clien_data对象，但为了提高poll性能，仍有必要限制用户数量
    pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for (int i = 0; i <= user_counter; i++)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }

    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while (1)
    {
        ret = poll(fds, user_counter + 1, -1);
        if (ret < 0)
        {
            printf("poll失败\n");
            break;
        }

        for (int i = 0; i < user_counter + 1; i++)
        {
            if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN))
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_length = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_length);
                if (connfd < 0)
                {
                    printf("errno is:%d\n", errno);
                    continue;
                }

                // 如果请求太多，则关闭新到的连接
                if (user_counter >= USER_LIMIT)
                {
                    const char *info = "服务器爆满\n";
                    printf("%s", info);
                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }

                // 对于新的连接，同时修改fds和users数组
                user_counter++;
                users[connfd].address = client_addr;
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                printf("新加入一个用户,现在有%d个用户\n", user_counter);
            }
            else if (fds[i].revents & POLLERR)
            {
                printf("错误来自:%d\n", fds[i].fd);
                char errors[100];
                memset(errors, '\0', 100);
                socklen_t length = sizeof(errors);
                if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0)
                {
                    printf("获取socket option失败\n");
                }
                continue;
            }
            else if (fds[i].revents & POLLRDHUP)
            {
                // 如果客户端关闭连接，则服务器也关闭对应连接，并将总用户数-1
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                printf("有一个客户端离开了\n");
            }
            else if (fds[i].revents & POLLIN)
            {
                int connfd = fds[i].fd;
                memset(users[connfd].buf, '\0', BUFFER_SIZE);
                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE - 1, 0);
                if (ret < 0)
                {
                    // 如果读操作出错，则关闭连接
                    if (errno != EAGAIN)
                    {
                        close(connfd);
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }
                else if (ret == 0)
                {
                    /* code */
                }
                else
                {
                    // 如果接收到客户端数据，则通知其他socket连接准备读写数据
                    for (int j = 1; j <= user_counter; j++)
                    {
                        if (fds[j].fd == connfd)
                        {
                            continue;
                        }
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if (fds[i].revents & POLLOUT)
            {
                int connfd = fds[i].fd;
                if (!users[connfd].write_buf)
                {
                    continue;
                }

                ret = send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
                users[connfd].write_buf = NULL;

                // 写完数据后 需要重新注册fds[i]的可读事件
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }

    delete[] users;
    close(listenfd);
    return 0;
}