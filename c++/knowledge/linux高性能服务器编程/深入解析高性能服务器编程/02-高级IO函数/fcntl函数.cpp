#include <fcntl.h>

/// @brief file control,对文件描述符的各种控制操作
/// @param fd  被控制的文件描述符
/// @param cmd  指定执行何种类型的操作
/// @param
/// @return
int fcntl(int fd, int cmd, ...) {}

// 将文件描述符设置为非阻塞的
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);      // 获取文件描述符 旧的状态标志
    int new_option = old_option | O_NONBLOCK; // 设置非阻塞标志
    fcntl(fd, F_SETFL, new_option);
    return old_option; // 返回文件描述符旧的状态标志， 以便后续恢复该状态标志
}