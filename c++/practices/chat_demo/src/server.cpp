/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 00:37:19
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 11:38:36
 * @FilePath: /c++/practices/chat_demo/src/server.cpp
 * @Description: 注释信息
 */
#include "server.h"

server::server(/* args */)
{
    // 初始化服务器地址和端口
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 初始化socket
    listener = 0;

    // epoll fd
    epfd = 0;
}

// 初始化服务端并启动监听
void server::init_server()
{
    std::cout << "Init server..." << std::endl;

    // 创建监听socket
    listener = socket(PF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("listener");
        exit(-1);
    }

    // 绑定地址
    if (bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind error");
        exit(-1);
    }

    // 监听
    int ret = listen(listener, 5);
    if (ret < 0)
    {
        perror("listen error");
        exit(-1);
    }

    std::cout << "Start to listen: " << SERVER_IP << std::endl;

    // 在内核中创建事件表
    epfd = epoll_create(EPOLLL_SIZE);

    if (epfd < 0)
    {
        perror("epfd error");
        exit(-1);
    }

    // 往事件表里添加 监听事件
    addfd(epfd, listener, true);
}

// 关闭服务，清理并关闭文件描述符
void server::close_server()
{
    // 关闭socket
    close(listener);

    // 关闭epoll监听
    close(epfd);
}

// 发送广播消息给所有客户端
int server::send_broadcast_message(int clientfd)
{
    // buf[BUF_SIZE] 接受新消息
    // message[BUF_SIZE] 保存格式化的消息
    char buf[BUF_SIZE], message[BUF_SIZE];
    bzero(buf, BUF_SIZE);
    bzero(message, BUF_SIZE);

    // 接收新消息
    std::cout << "read from client(clientID = " << clientfd << ")" << std::endl;
    int len = recv(clientfd, buf, BUF_SIZE, 0);

    // 如果客户端关闭了连接
    if (len == 0)
    {
        close(clientfd);

        // 在客户端列表中删除该客户端
        clients_list.remove(clientfd);
        std::cout << "clientId = " << clientfd
                  << "closed. \n now there are "
                  << clients_list.size()
                  << "clients in the room"
                  << std::endl;
    }
    //  发送广播消息给所有客户端
    else
    {
        //判断聊天室是否还有其他客户端
        if (clients_list.size() == 1)
        {
            //发送提示消息
            send(clientfd, CAUTION, strlen(CAUTION), 0);
            return 0;
        }

        // 格式化发送的内容
        sprintf(message, SERVER_MESSAGE, clientfd, buf);

        // 遍历客户端列表依次发送消息，需要判断不用给来源客户端发
        std::list<int>::iterator it;
        for (it = clients_list.begin(); it != clients_list.end(); ++it)
        {
            if (*it != clientfd)
            {
                if (send(*it, message, BUF_SIZE, 0) < 0)
                {
                    return -1;
                }
            }
        }
    }
    return len;
}

// 启动服务端
void server::start_server()
{
    // epoll 事件队列
    static struct epoll_event events[EPOLLL_SIZE];

    // 初始化服务端
    init_server();

    // 主循环
    while (1)
    {
        // epoll_events_count 表示就绪事件的数目
        int epoll_events_count = epoll_wait(epfd, events, EPOLLL_SIZE, -1);

        if (epoll_events_count < 0)
        {
            perror("epoll failure");
            break;
        }

        std::cout << "epoll_events_count = \n"
                  << epoll_events_count << std::endl;
        // 处理epoll_events_count 个就绪事件
        for (int i = 0; i < epoll_events_count; i++)
        {
            int sockfd = events[i].data.fd;

            //新用户连接
            if (sockfd == listener)
            {
                struct sockaddr_in client_address;
                socklen_t client_addLength = sizeof(struct sockaddr_in);
                int clientfd = accept(listener, (struct sockaddr *)&client_address, &client_addLength);

                std::cout << "client connection from"
                          << inet_ntoa(client_address.sin_addr) << ":"
                          << ntohs(client_address.sin_port) << ", clientfd= "
                          << clientfd << std::endl;

                addfd(epfd, clientfd, true);

                // 服务端用list保存用户连接
                clients_list.push_back(clientfd);
                std::cout << "Add new clientfd = " << clientfd << "to epoll" << std::endl;
                std::cout << "Now there are " << clients_list.size() << "clients in the room" << std::endl;

                // 服务端发送欢迎消息
                std::cout << "welcome message" << std::endl;

                char message[BUF_SIZE];
                bzero(message, BUF_SIZE);
                sprintf(message, SERVER_WELCOME, clientfd);
                int ret = send(clientfd, message, BUF_SIZE, 0);
                if (ret < 0)
                {
                    perror("send error");
                    close_server();
                    exit(-1);
                }
            }

            // 处理用户发来的消息，并广播，使其他用户收到信息
            else
            {
                int ret = send_broadcast_message(sockfd);
                if (ret < 0)
                {
                    perror("error");
                    close_server();
                    exit(-1);
                }
            }
        }
    }

    // 关闭服务
    close_server();
}

server::~server()
{
}