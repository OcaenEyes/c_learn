#include <fcntl.h>

/// @brief file control,对文件描述符的各种控制操作
/// @param fd  被控制的文件描述符
/// @param cmd  指定执行何种类型的操作
/// @param
/// @return
int fcntl(int fd, int cmd, ...) {}