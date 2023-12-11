/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-08 04:14:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-10 00:32:39
 * @FilePath: /c++/oceanim/client.cpp
 * @Description: 客户端
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <mutex>
#include <ncurses.h>

#define SERVER_IP "127.0.0.1"
#define GROUP_CHAT_PORT 12345
#define NUM_THREADS 2

int serverSocket;       // 网络套接字
sockaddr_in serverAddr; // 网络地址
char nickname[32];      // 昵称
char line1[111];        // 一行分割线
char line2[111];        // 一行空白字符串
std::mutex mtx;         // 全局定义互斥锁

/// @brief 初始化
/// @return
bool init()
{
    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 初始化serverSocket
    bzero(&serverAddr, sizeof(serverAddr));                   // 设置服务器地址和端口
    serverAddr.sin_family = PF_INET;
    inet_pton(PF_INET, SERVER_IP, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(GROUP_CHAT_PORT);
    return true;
}

/// @brief 登录
void login()
{
    // system("mode con lines=5 cols=30\n");
    printf("    欢迎使用OCEANIM聊天~\n\n");
    printf("        昵称:");
    sscanf("%s", nickname, sizeof(nickname));
    while (getchar() != '\n')
        ; // 清空输入缓冲区
    send(serverSocket, nickname, strlen(nickname) + 1, 0);
}

/// @brief 初始化界面
void ui_init()
{ // 初始化ncurses库
    initscr();
    resize_term(36, 110);
    for (int i = 0; i < 110; i++)
    {
        line1[i] = '-';
        line2[i] = ' ';
    }
    line1[109] = 0;
    line2[109] = 0;
    move(30, 0);
    refresh();
    printw("%s\n", line1);
    refresh();
}

void printMsg(const char *msg)
{
    mtx.lock();                  // 加锁
    static int row = 0, col = 0; // static静态变量，第一次执行初始化
    move(row, col);
    refresh();

    printw("%s", msg); // 打印消息
    refresh();

    getyx(stdscr, row, col);
    mtx.unlock(); // 解锁
}

void *threadRecvMsg(void *args)
{
    char buff[4096];
    while (1)
    {
        int ret = recv(serverSocket, buff, sizeof(buff), 0);
        if (ret <= 0)
        {
            printw("服务器断开连接或故障！\n");
            refresh();
            break;
        }
        printMsg(buff);
    }
}

int main()
{

    if (!init())
    {
        printw("初始化失败！\n");
        refresh();
        return -1;
    }

    // 连接服务器
    int ret = connect(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret != 0)
    {
        printw("连接服务器失败！错误原因是:%d\n", errno);
        refresh();
        return -2;
    }

    login();   // 登录聊天室
    ui_init(); // 初始化界面

    // 定义线程的 id 变量，多个变量使用数组
    pthread_t threadpool[NUM_THREADS];
    ret = pthread_create(&threadpool[0], NULL, threadRecvMsg, NULL);
    if (ret != 0)
    {
        printw("pthread_create error: error_code=%d", ret);
        refresh();
        return -3;
    }

    printf("输入:");
    // 等待用户输入
    getch();

    char msg[4096];
    sscanf("%s", msg, sizeof(msg));
    while (getchar() != '\n')
        ;
    send(serverSocket, nickname, sizeof(msg), 0);
    // 关闭ncurses库
    endwin();
}
