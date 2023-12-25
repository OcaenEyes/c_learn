/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-02 21:10:57
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 09:56:08
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/mmap函数和munmap函数.cpp
 * @Description: 注释信息
 */
#include <sys/mman.h>

/**
 * @description: 申请一段内存空间， 可将该段内存作为进程间通信的共享内存，也可将文件直接映射到其中
 * @param {void} *start 允许用户使用某个特定的地址作为这段内存的起始地址， 如果设置为NULL，则系统自动分配一个地址
 * @param {size_t} length 该内存段的长度
 * @param {int} port 设置内存段的访问权限
 * @param {int} flags 控制内存段内容被修改后程序的行为
 * @param {int} fd 被映射文件对应的文件描述符， 一般通过open系统调用获得
 * @param {off_t} off_t 设置从文件的何处开始映射
 * @return {*} 成功则返回指向目标内存区域的指针 ，失败则返回MAP_FAILED((void*)-1)并设置errno
 */
void* mmap(void *start, size_t length, int port ,int flags, int fd, off_t off_t){}

/**
 * @description: 释放由mmap创建的这段内存空间
 * @param {void} *start
 * @param {size_t} length
 * @return {*} 成功则返回0 失败返回-1 并设置errno
 */
int munmap(void *start,size_t length){}