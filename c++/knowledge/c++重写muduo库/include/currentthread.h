/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-07 19:28:01
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-07 19:35:35
 * @FilePath: /c++/knowledge/c++重写muduo库/include/currentthread.h
 * @Description: 注释信息
 */
#pragma once

namespace ocean_muduo
{
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
