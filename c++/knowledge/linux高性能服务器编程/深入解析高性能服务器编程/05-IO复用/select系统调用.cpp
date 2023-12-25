#include <sys/select.h>

/// @brief select API
/// @param nfds 指定被监听的文件描述符的总数。 通常被设置为select监听的所有描述符中最大值+1(因为文件描述符是从0 开始计数的)
/// @param readfds 可读事件对应的文件描述符集合
/// @param writefds 可写事件对应的文件描述符集合
/// @param exceptfds 异常事件对应的文件描述符集合
/// 应用程序调用select 函数时，通过这3 个参数传人自己感兴趣的文件描述符。 sclect 调用返回时，内核将修改它们来通知应用程序哪些文件描述符已经就绪
/// @param timeout 设置select函数的超时时间，是一个timeval结构类型指针； 采用指针式因为内核将修改它以告诉应用程序select等待了多久
/// @return
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {}

// 由于位操作过于烦琐，我们应该使用下面的一系列宏来访问fd_set 结构体中的位:

FD_ZERO(fd_set *fdset);              /*清除fdest的所有位*/
FD_SET(int fd, fd_set *fdest);       /*设置fdest的位fd*/
FD_CLR(int fd, fd_set *fdset);       /* 清除fdset 的位fd */
int FD_ISSET(int fd, fd_set *fdset); /* 测试fdset的位fd是否被设置*/

struct timeval
{
    long tv_sec;  // 秒数
    long tv_usec; // 微秒数
};

/**
 * # 文件描述符的就绪条件
 *      ## 以下情况socket可读：
 *          - socket 内核接收缓存区中的字节数大于或等于其低水位标记SO_RCVLOWAT。此时 我们可以无阻塞地读该socket ，并且读操作返回的字节数大于0。
 *          - socket 通信的对方关闭连接。此时对该socket 的读操作将返回0。
 *          - 监听socket 上有新的连接请求。
 *          - socket 上有未处理的错误。此时我们可以使用getsockopt 来读取和清除该错误
 *      ## 以下情况socket可写：
 *          - socket 内核发送缓存区中的可用字节数大于或等于其低水位标记SO_SNDLOWAT。 此时我们可以无阻塞地写该socket，并且写操作返回的字节数大于0。
 *          - socket的写操作被关闭。 对写操作被关闭的socket执行写操作将触发一个SIGPIPE信号
 *          - socket使用非阻塞connect连接成功或失败（超时）之后
 *          - socket上有未处理的错误。 此时我们可使用getsockopt来读取和清除该错误
 *      ## select能处理的异常情况只有一种： socket上接收到带外数据
 *
 */