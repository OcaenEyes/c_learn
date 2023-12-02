/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-02 10:58:03
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-02 14:00:52
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/web服务器上的集中写.cpp
 * @Description: 注释信息
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/* 定义两种HHTP状态码和状态信息 */
static const char *status_line[2] = {"200 OK", "500 internal server error"};

int main(int argc, char *argv[])
{
    if (argc <= 3)
    {
        printf("usage: %s ip_address port_number filename\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    // 将目标文件作为 程序的第三个参数传入
    const char *file_name = argv[3];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlen = sizeof(client);

    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlen);
    if (connfd < 0)
    {
        printf("errno is : %d\n", errno);
    }
    else
    {
        // 用于保存HTTP应答的状态行、头部字段、 和一个空行的缓存区
        char header_buf[BUFFER_SIZE];
        memset(header_buf, '\0', BUFFER_SIZE);

        // 用于存放目标文件内容的应用程序缓存
        char *file_buf;

        // 用于获取目标文件的属性，比如是否为目录，文件大小等
        struct stat file_stat;

        // 记录目标文件是否是有效文件
        bool valid = true;

        // 缓存区 header_buf 目前已使用了多少字节的空间
        int len = 0;
        if (stat(file_name, &file_stat) < 0) // 目标文件不存在
        {
            valid = false;
        }
        else
        {
            if (S_ISDIR(file_stat.st_mode)) // 目标文件是一个目录
            {
                valid = false;
            }
            else if (file_stat.st_mode & S_IROTH) // 当前用户有读取目标文件的权限
            {
                /* 动态分配缓存区file_buf,并指定其大小为目标文件的大小 file_stat.st_size 加1， 然后将目标文件读入缓存区file_buf */
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size + 1];
                memset(file_buf, '\0', file_stat.st_size + 1);

                if (read(fd, file_buf, file_stat.st_size) < 0)
                {
                    valid = false;
                }
            }
            else
            {
                valid = false;
            }
        }
    }
}