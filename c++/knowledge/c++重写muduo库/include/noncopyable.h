/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-05 11:50:22
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-05 11:54:08
 * @FilePath: /c++/knowledge/c++重写muduo库/include/noncopyable.h
 * @Description: noncopyable基类
 */
#pragma once

namespace ocean_muduo
{
    /**
     * @brief noncopyable被继承后， 派生类对象可以构造和析构，但不能进行拷贝构造和赋值操作
     */
    class noncopyable
    {
    protected:
        // 默认构造函数
        noncopyable() = default;
        // 默认析构函数
        ~noncopyable() = default;

    public:
        // 禁用拷贝构造
        noncopyable(const noncopyable &) = delete;
        // 禁用赋值操作
        noncopyable &operator=(const noncopyable &) = delete;
    };

} // namespace ocean_muduo
