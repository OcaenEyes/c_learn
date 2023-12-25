#include <sys/sendfile.h>

/// @brief sendfile函数，在两个文件描述符之间直接传递数据(完全在内核中操作)，从而避免了内核缓冲区和用户缓冲区之间的数据拷贝【0拷贝】
/// @param out_fd 待写入内容的文件描述符
/// @param in_fd 待读出内容的文件描述符, [必须指向真实文件]
/// @param offset 指定从读入文件流的哪个位置开始读，如果为空，则使用读入文件流默认的起始位置
/// @param count 指定在文件描述符in_fd和out_fd之间传输的字节数
/// @return 成功返回传输的字节数，失败则返回-1并设置errno
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count) {}