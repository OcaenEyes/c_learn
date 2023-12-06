/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-0608:48:46
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-06 22:28:59
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/05-IO复用/IO复用-高级应用/同时处理TCP和UDP的服务/server.cpp
 * @Description: 同时处理TCP和UDP的回射服务器
 *
 *
 *
 * 1)从bind系统调用的参数来看，一个socket只能与一个socket地址绑定，即一个socket只能用来监听一个端口。
 * 2)因此，服务器如果要同时监听多个端口，就必须创建多个socket，并将它们分别绑定到各个端口上。
 * 3)这样一来，服务器程序就需要同时管理多个监听socket，I/O复用技术就有了用武之地。
 * 4)另外，即使是同一个端口，如果服务器要同时处理该端又上的TCP和UDP请求，则也需要创建两个不同的socket:一个是流socket，另一个是数据报socket，并将它们都绑定到该端口上
 */

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
#include <sys/epoll.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SZIE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

/// @brief 将文件描述符fd上的EPOLLIN 注册到epollf指示的epoll内核事件表中
/// @param epollfd
/// @param fd
void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("应用程序:%s需要输入IP地址 Port端口号参数\n", basename(argv[0]));
        return 1;
    }
    char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    /**
     * inet_pton() 函数是 “Internet presentation to network” 的缩写，用于将 IP 地址的表现形式（例如字符串形式的 “127.0.0.1”）转换为其网络字节序的二进制形式。这个函数支持 IPv4 和 IPv6 地址
     */
    inet_pton(AF_INET, ip, &address.sin_addr);

    /**
     * unsigned short ntohs(unsigned short);  将16位的网络字节序转换为主机字节序
     * unsigned long ntohl(unsigned long);    将32位的网络字节序转换为主机字节序
     * unsigned short htons(unsigned short ); 将16位的主机字节序转换为网络字节序
     * unsigned long  htonl (unsigned long);  将32位的主机字节序转换为网络字节序
     */
    address.sin_port = htons(port);

    // 创建TCP socket,并将其绑当到端口port上
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);
    ret = listen(listenfd, 5);
    assert(ret != -1);

    // 创建UDP socket,并将其绑定到端口port上
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int udpfd = socket(PF_INET, SOCK_DGRAM, 0);
    assert(udpfd >= 0);
    ret = bind(udpfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    // 注册TCPsocket 和UDPsocket 上的可读事件
    addfd(epollfd, listenfd);
    addfd(epollfd, udpfd);

    while (1)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (number < 0)
        {
            printf("epoll失败\n");
            break;
        }
        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_length = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_length);
                addfd(epollfd, connfd);
            }
            else if (sockfd == udpfd)
            {
                char buf[UDP_BUFFER_SIZE];
                memset(buf, '\0', UDP_BUFFER_SIZE);
                struct sockaddr_in client_addr;
                socklen_t client_addr_length = sizeof(client_addr);

                ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
                               (struct sockaddr *)&client_addr, &client_addr_length);

                if (ret > 0)
                {
                    sendto(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
                           (struct sockaddr *)&client_addr, client_addr_length);
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                char buf[TCP_BUFFER_SZIE];
                while (1)
                {
                    memset(buf, '\0', TCP_BUFFER_SZIE);
                    ret = recv(sockfd, buf, TCP_BUFFER_SZIE - 1, 0);
                    if (ret < 0)
                    {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                        {
                            break;
                        }
                        close(sockfd);
                        break;
                    }
                    else if (ret == 0)
                    {
                        close(sockfd);
                    }
                    else
                    {
                        send(sockfd, buf, ret, 0);
                    }
                }
            }
            else{
                printf("something else hapened\n");
            }
        }
    }
    close(listenfd);
    return 0;
}