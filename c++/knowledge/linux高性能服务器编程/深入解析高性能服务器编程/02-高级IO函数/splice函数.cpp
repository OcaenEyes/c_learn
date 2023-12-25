#include <sys/types.h>
#include <fcntl.h>

/// @brief  用于在两个文件描述符之间移动数据， 【0拷贝操作】
/// @param fd_in 待输入数据的文件描述符 【如果fd_in是一个管道文件描述符，那么off_in参数必须设置为NULL】
/// @param off_in  如果fd_in不是管道文件描述符，那么off_in表示从输入数据流的何处开始读取数据
/// @param fd_out
/// @param off_out
/// @param len  移动数据的长度
/// @param flags 控制数据如何移动
/// @return
ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags) {}