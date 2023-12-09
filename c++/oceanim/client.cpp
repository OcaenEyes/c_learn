/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-08 04:14:36
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-08 15:24:45
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

#define SERVER_IP "127.0.0.1"
#define GROUP_CHAT_PORT 12345

// 清除屏幕
#define CLEAR() printf("\033[2J")

// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))

// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))

// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))

// 右移光标
#define MOVERIGHT(y) printf("\033[%dC", (y))

// 定位光标
#define MOVETO(x, y) printf("\033[%d;%dH", (x), (y))

// 光标复位
#define RESET_CURSOR() printf("\033[H")

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")

// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

// 反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")

int serverSocket;       // 网络套接字
sockaddr_in serverAddr; // 网络地址
char nickname[32];      // 昵称
char line1[111];        // 一行分割线
char line2[111];        // 一行空白字符串

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
{
    CLEAR();
    struct winsize win;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) < 0)
    {
        printf("获取terminal size失败\n");
        return;
    }
    printf("当前terminal size:%d行，%d列\n", win.ws_row, win.ws_col);

    win.ws_row = 50;  // 设置新的行数
    win.ws_col = 100; // 设置新的列数

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) < 0)
    {
        printf("更新设置terminal size失败\n");
        return;
    }
    printf("更新后的terminal size:%d行，%d列", win.ws_row, win.ws_col);

    // system("resize -s 36 110");
    // MOVETO(0, 33);
    for (int i = 0; i < 110; i++)
    {
        line1[i] = '-';
        line2[i] = ' ';
    }
    line1[110] = 0;
    line2[110] = 0;
    printf("%s", line1);
}

int main()
{

    if (!init())
    {
        printf("初始化失败！\n");
        // return -1;
    }

    // 连接服务器
    int ret = connect(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret != 0)
    {
        printf("连接服务器失败！错误原因是:%d\n", errno);
        // return -2;
    }

    // login();   // 登录聊天室
    ui_init(); // 初始化界面
}