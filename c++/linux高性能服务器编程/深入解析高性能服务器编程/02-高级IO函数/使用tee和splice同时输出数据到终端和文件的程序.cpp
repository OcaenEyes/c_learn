/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 12:54:37
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 16:02:53
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/02-高级IO函数/使用tee和splice同时输出数据到终端和文件的程序.cpp
 * @Description: 注释信息
 */
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage:%s <file>\n", argv[0]);
        return 1;
    }
    int filefd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    assert(filefd > 0);

    int pipefd_stdout[2];
    int ret = pipe(pipefd_stdout);
    assert(ret != -1);

    int pipefd_file[2];
    ret = pipe(pipefd_file);
    assert(ret != -1);

    // 将标准输入内容输入管道 pipefd_stdout
    ret = splice(STDIN_FILENO, NULL, pipefd_stdout[1], NULL,
                 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
    assert(ret != -1);

    // 将管道pipefd_stdout的输出文件复制到 管道pipefd_file的输入端
    ret = tee(pipefd_stdout[0], pipefd_file[1], 32768, SPLICE_F_NONBLOCK);
    assert(ret != -1);

    // 将管道pipefd_file的输出 定向到文件描述符filefd上，从而将标准输入的内容写入文件
    ret = splice(pipefd_file[0], NULL, filefd, NULL,
                 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
    assert(ret != -1);

    // 将管道pipefd_stdout的输出定向到标准输出，其内容和写入文件的内容完全一致
    ret = splice(pipefd_stdout[0], NULL, STDOUT_FILENO, NULL,
                 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
    assert(ret != -1);

    close(pipefd_file[0]);
    close(pipefd_file[1]);

    return 0;
}