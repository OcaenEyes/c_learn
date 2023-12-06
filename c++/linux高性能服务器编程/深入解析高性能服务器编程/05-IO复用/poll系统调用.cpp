#include <poll.h>

/// @brief 在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪
/// @param fds  pollfd结构类型的数组，指定所有我们感兴趣的文件描述符上发生的可读、可写和异常等事件
/// @param nfds 指定被监听事件集合fds的大小
/// @param timeout 指定poll的超时值，单位是毫秒； 当timeout为-1时，poll调用将永远阻塞，直到某个事件发生； 当timeout为0时，poll调用立即返回
/// @return
int poll(struct pollfd *fds, nfds_t nfds, int timeout) {}

struct pollfd
{
    int fd;        // 文件描述符
    short events;  // 注册的事件--> 告诉poll监听fd上的哪些事件， 它是一系列事件的按位或
    short revents; // 实际发生的事件，由内核填充----> 由内核修改，以通知应用程序fd上实际发生了哪些事件
};

typedef unsigned long int nfds_t;