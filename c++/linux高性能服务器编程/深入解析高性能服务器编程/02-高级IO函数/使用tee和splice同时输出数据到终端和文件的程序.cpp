/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 12:54:37
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 12:54:37
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/使用tee和splice同时输出数据到终端和文件的程序.cpp
 * @Description: 注释信息
 */
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc !=2)
    {
        printf("usage:%s <file>\n", argv[0]);
        return 1;
    }
    int filefd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0666);
    assert(filefd >0);

    int pipefd_stdout[2];
    int ret = pipe(pipefd_stdout);
    assert(ret != -1);

    int pipefd_file[2];
    int ret = pipe(pipefd_file);
    assert(ret != -1);
    
    // 将标准输入内容输入管道 Pipefd_stdout
    ret = splice()
}