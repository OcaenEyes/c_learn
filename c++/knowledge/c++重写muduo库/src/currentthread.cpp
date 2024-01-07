/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 19:28:16
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-07 19:28:16
 * @FilePath: /c++/knowledge/c++重写muduo库/src/currentthread.cpp
 * @Description: 注释信息
 */
#include "currentthread.h"

    #include <unistd.h>
       #include <sys/syscall.h> 

namespace ocean_muduo
{
    __thread int t_cached_tid=0;

    void cached_tid(){
        if(t_cached_tid ==0){
            // 通过Linux系统调用，获取当前线程的tid值
            t_cached_tid = static_cast<pid_t>(::syscall(SYS_getted));
        }
    }
} // namespace ocean_muduo
