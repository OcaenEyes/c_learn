/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 21:42:37
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 22:34:07
 * @FilePath: /c++/practices/chat_demo/src/client.cpp
 * @Description: 注释信息
 */
#include "client.h"

client::client(/* args */)
{
    // 初始化 要连接的服务器地址 和端口
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 初始化socket
    sock = 0;
    // 初始化进程号
    pid = 0;
    // 客户端状态
    isClientWork = true;
    // epoll fd
    epfd = 0;
}

// 连接服务器
void client::connect_sever()
{
    std::cout << "connect server: " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    // 创建socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("sock error");
        exit(-1);
    }

    // 连接服务端
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect error");
        exit(-1);
    }

    // 创建管道，其中fd[0]用于父进程读， fd[1]用于子进程写
    if (pipe(pipe_fd) < 0)
    {
        perror("pipe error");
        exit(-1);
    }

    // 创建epoll
    epfd = epoll_create(EPOLLL_SIZE);

    if (epfd < 0)
    {
        perror("epfd error");
        exit(-1);
    }

    // 将sock和管道读端 描述符都添加到内核事件表中
    addfd(epfd, sock, true);
    addfd(epfd, pipe_fd[0], true);
}
// 断开连接，清理饼关闭文件描述符
void client::close_connect()
{
    if (pid)
    {
        // 关闭父进程的管道和 sock
        close(pipe_fd[0]);
        close(sock);
    }
    else
    {
        // 关闭子进程的管道
        close(pipe_fd[1]);
    }
}

// 启动客户端
void client::start_client()
{
    // epoll 事件队列
    static struct epoll_event events[2];

    // 连接服务器
    connect_sever();

    // 创建子进程
    pid = fork();

    // 如果创建子进程失败 则退出
    if (pid < 0)
    {
        perror("fork error");
        close(sock);
        exit(-1);
    }
    else if (pid == 0)
    {
        // 进入子进程执行流程
        // 子进程负责写入管道， 因此先关闭读端
        close(pipe_fd[0]);

        //输入exit可以退出聊天室
        std::cout << "please inpu 'exit' to exit the char room " << std::endl;

        // 如果客户端运行正常 ，则不断读取输入发送给服务端
        while (isClientWork)
        {
            bzero(&message, BUF_SIZE);
            fgets(message, BUF_SIZE, stdin);

            // 客户端输入 exit， 退出
            if (strncasecmp(message, EXIT, strlen(EXIT)) == 0)
            {
                isClientWork = 0;
            }
            // 子进程将信息写入管道
            else
            {
                if (write(pipe_fd[1], message, strlen(message) - 1) < 0)
                {
                    perror("fork error");
                    exit(-1);
                }
            }
        }
    }
    else
    {
        // pid >0 父进程
        // 父进程 负责读管道数据， 因此先关闭写端
        close(pipe_fd[1]);

        // 主循环(epoll_wait)
        while (isClientWork)
        {
            int epoll_events_count = epoll_wait(epfd, events, 2, -1);
            // 处理就绪事件
            for (int i = 0; i < epoll_events_count; ++i)
            {
                bzero(&message, BUF_SIZE);
                // 服务端发来消息
                if (events[i].data.fd == sock)
                {
                    // 接受服务端消息
                    int ret = recv(sock, message, BUF_SIZE, 0);

                    // ret =0 服务端关闭
                    if (ret == 0)
                    {
                        std::cout << "server closed connection: " << sock << std::endl;
                        close(sock);
                        isClientWork = 0;
                    }
                    else
                    {
                        std::cout << message << std::endl;
                    }
                }
                // 子进程写入事件发生，父进程处理并发送服务端
                else
                {
                    // 父进程从管道中读取数据
                    int ret = read(events[i].data.fd, message, BUF_SIZE);

                    // ret =0
                    if (ret == 0)
                    {
                        isClientWork = 0;
                    }
                    else
                    {
                        // 将消息发给服务端
                        send(sock, message, BUF_SIZE, 0);
                    }
                }
            }
        }
    }

    close_connect();
}
client::~client()
{
}
