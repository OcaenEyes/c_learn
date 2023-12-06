/**
 * 即使我们使用ET模式，一个socket上的某个事件还是可能被触发多次。
 * 这在并发程序中就会引起一个问题。比如一个线程(或进程，下同)在读取完某个socket 上的数据后,开始处理这些数据，
 *  而在数据的处理过中该socket上又有新数据可读 (EPOLLIN再次被触发)，此时另外一个线程被唤醒来读取这些新的数据。于是就出现 了两个线程同时操作 一个 socket 的局面
 *
 * 期望：一个socket连接在任一时刻都只被一个线程处理，可使用EPOLLONESHOT事件实现
 *
 * 对于注册了EPOLLONESHOT事件的文件描述符：
 *  - 操作系统最多触发其上注册的一个可读、可写或者异常事件，且只触发一次
 *  - 除非我们使用epoll_ctl函数重制该文件描述符上注册的EPOLLONESHOT事件
 *  - 这样，当一个线程在处理某个socket时，其他线程是不可能有机会操作该socket的 。
 *  - 但，反过来注册了EPOLLONESHOT事件的socket一旦被某个线程处理完毕，该线程就应该立即重置这个socket 上的EPOLLONESHOT事件，以确保这个 socket 下一次可读时，其EPOLLIN事件能被触发，进而
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
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds
{
    int epollfd;
    int sockfd;
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

// 将fd上的EPOLLIN和EPOLLET事件注册到epollfd指示的epoll内核事件表中，参数oneshot指定是否注册fd上的EPOLLONESHOT事件
void addfd(int epollfd, int fd, bool oneshot)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (oneshot)
    {
        event.events |= EPOLLONESHOT;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

// 重置fd上的事件。 这样操作之后，尽管fd上的EPOLLONESHOT事件被注册，但操作系统仍会触发fd上的EPOLLIN事件，且只触发一次
void reset_oneshot(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

// 工作线程
void *worker(void *arg)
{
    int sockfd = ((fds *)arg)->sockfd;
    int epollfd = ((fds *)arg)->epollfd;
    printf("start new thread to receive data on fd:%d\n", sockfd);

    char buf[BUFFER_SIZE];
    memset(buf, '\0', BUFFER_SIZE);
    // 循环读取额sockfd上的数据，直到遇到EAGAIN错误
    while (1)
    {
        int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
        if (ret == 0)
        {
            close(sockfd);
            printf("foreiner closed the connection\n");
            break;
        }
        else if (ret < 0)
        {
            if (errno == EAGAIN)
            {
                reset_oneshot(epollfd, sockfd);
                printf("read later\n");
                break;
            }
        }
        else
        {
            printf("get content: %s\n", buf);
            sleep(5); // 休眠5S，模拟数据处理过程
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage:%s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
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

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    // 注意 监听socket listenfd上不能注册EPOLLONESHOT事件，否则应用程序只能处理一个客户连接 【因为后续的客户连接请求将不再触发listenfd上的EPOLLIN事件】
    addfd(epollfd, listenfd, false);

    while (1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0)
        {
            printf("epoll failure\n");
            break;
        }
        for (int i = 0; i < ret; i++)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_length = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_length);

                // 对每个非监听文件描述符都注册EPOLLONESHOT事件
                addfd(epollfd, connfd, true);
            }
            else if (events[i].events & EPOLLIN)
            {
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;

                // 新启动一个工作线程为sockfd服务
                pthread_create(&thread, NULL, worker, (void *)&fds_for_new_worker);
            }
            else
            {
                printf("something else happened\n");
            }
        }
    }
    close(listenfd);
    return 0;
}