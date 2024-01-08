/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 19:28:01
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-07 13:05:34
 * @FilePath: /c++/knowledge/c++重写muduo库/include/currentthread.h
 * @Description: 注释信息
 */
#pragma once

namespace ocean_muduo
{
    // extrn 表明变量或者函数是定义在其他其他文件中的
    extern __thread int t_cached_tid;

    void cached_tid();

    inline int tid()
    {
        if (__builtin_expect(t_cached_tid == 0, 0))
        {
            cached_tid();
        }
        return t_cached_tid;
    }

} // namespace ocean_muduo
