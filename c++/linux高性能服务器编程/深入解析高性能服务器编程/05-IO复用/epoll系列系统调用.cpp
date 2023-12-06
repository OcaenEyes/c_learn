#include <sys/epoll.h>
#include <sys/poll.h>

/// @brief 创建一个文件描述符，来唯一标识内核中的【用户关心的文件描述符上的事件--组成的事件表】
/// @param size 提示事件表需要多大
/// @return
int epoll_create(int size) {}

/// @brief 操作epoll的内核事件表
/// @param epfd
/// @param op 指定操作类型，有3种
///         【EPOLL_CTL_ADD 往事件表中注册fd上的事件  、EPOLL_CTL_MOD 修改fd上的注册事件、EPOLL_CTL_DEL删除fd上的注册事件】
/// @param fd 要操作的文件描述符
/// @param event 指定事件，是epoll_event结构指针类型
/// @return 成功则返回0，失败则返回-1并设置errno
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {}

struct epoll_event
{
    __uint32_t events; // epoll事件，描述事件类型
    epoll_data_t data; // 用户数据
};

typedef union epoll_data
{
    void *ptr; // 用来指定与fd相关的用户数据
    int fd;    // 使用最多，指定事件所从属的目标文件描述符
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

/// @brief 在一段超时时间内，等待一组文件描述符上的事件
/// @param epfd
/// @param events
/// @param maxevents 指定最多监听多少个事件，必须大于0
/// @param timeout 超时参数
/// @return 成功时返回就绪的文件描述符个数，失败则返回-1并设置errno
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {}

/**
 * epoll_wait函数如果检测到事件，就将所有就绪的事件从内核事件表(由epfd参数指定)中复制到它的第二个参数events 指向的数组中。
 * 这个数组只用于输出epoll_wait检测到的就绪事件，而不像select 和poll的数组参数那样既用于传入用户注册的事件，又用于输出 内核检测到的就绪事件。这就极大地提高了应用程序索引就绪文件描述符的效率。
 */

/**
 *  -- poll和epoll在使用上的差别--
 * **************************
 * 如何索引poll返回的就绪文件描述符
 * int ret = poll(fds, MAX_EVENT_NUMBER, -1);
 * 必须過历所有已注册文件描迷符并找到其中的就绪者(当然，可以利用ret 来稍做优化)
 * for (int i = 0; i < MAX_EVENT_NUMBER; i++)
 * {
 *      if (fds[i].revents & POLLIN) // 判断第i个文件描述符是否就绪
 *      {
 *          int sockfd = fds[i].fd;
 *          // 处理sockfd
 *       } 
 *  }
 * ***************************
 * 如何索引epoll返回的就绪文件描述符
 * int ret = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
 * 遍历就绪的ret个文件描述符
 * for(int i=0; i<ret;i++)
 * {
 *      int sockfd = events[i].data.fd;
 *      // sockfd肯定就绪，直接处理
 * }
 * 
*/


