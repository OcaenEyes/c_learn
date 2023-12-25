/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-02 09:55:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-02 10:09:20
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/readv和writev函数.cpp
 * @Description: 注释信息
 */
#include <sys/uio.h>

/**
 * @description: 将数据从文件描述符读到分散的内存块中，即分散读 
 * @param {int} fd 被操作的文件描述符
 * @param {iovec} *vector 表示iovec结构数组， iovec描述一块内存区
 * @param {int} count 表示vector数组的长度，即有多少块内存数据需要从fd读出
 * @return {*} 成功则返回读出fd的字节数， 失败则返回-1并设置errno
 */
ssize_t readv(int fd, const struct iovec *vector, int count) {}

/**
 * @description: 将多块分散的内存数据一并写入文件描述符中，即集中写
 * @param {int} fd 被操作的文件描述符
 * @param {iovec} *vector 表示iovec结构数组， iovec描述一块内存区
 * @param {int} count 表示vector数组的长度，即有多少块内存数据需要写入fd
 * @return {*} 成功则返回写入fd的字节数， 失败则返回-1并设置errno
 */
ssize_t writev(int fd, const struct iovec *vector, int count) {}