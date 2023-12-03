/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-03 19:32:21
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-03 19:40:25
 * @FilePath: /c++/linux高性能服务器编程/深入解析高性能服务器编程/03-Linux服务器程序规范/将服务器程序以守护进程的方式运行.cpp
 * @Description: 注释信息
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

bool daemonize()
{
    // 创建子进程，关闭父进程， 这样可是程序在后台运行
    pid_t pid = fork();
    if (pid < 0)
    {
        return false;
    }
    else if (pid > 0)
    {
        exit(0);
    }

    // 设置文件权限掩码， 当进程创建新文件(使用open(const char*pathname, int flags, mode_t mode) 系统调用)时， 文件的权限将是mode & 0777
    umask(0);

    // 创建新的会话， 设置本进程为进程组的首领
    pid_t sid = setsid();
    if (sid < 0)
    {
        return false;
    }

    // 切换工作目录
    if ((chdir("/")) < 0)
    {
        return false;
    }

    // 关闭标准输入设备、 标准输出设备 和标准错误输出设备
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 关闭其他已打开的文件描述符---代码省略

    // 将标准输入、标准输出和标准错误输出都定向到 /dev/null文件
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    return true;
}

// linux系统提供的库函数
int daemon(int nochdir, int noclose) {}