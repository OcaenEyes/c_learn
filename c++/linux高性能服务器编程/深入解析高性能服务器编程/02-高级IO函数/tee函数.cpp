/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 09:57:38
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 10:06:32
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/tee函数.cpp
 * @Description: 注释信息
 */
#include <sys/types.h>
#include <fcntl.h>

/**
 * @description:  在两个管道文件描述符之间复制数据，也是0拷贝操作
 * @param {int} fd_in 管道文件描述符
 * @param {int} fd_out 管道文件描述符
 * @param {size_t} len
 * @param {unsigned int} flags
 * @return {*} 成功则返回两个文件描述符之间复制的数据数量(字节数)
 */
ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags ) {}