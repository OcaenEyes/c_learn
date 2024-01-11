/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 07:36:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-11 21:57:53
 * @FilePath: /c++/knowledge/c++重写muduo库/include/buffer.h
 * @Description: 注释信息
 */
#pragma once

#include <vector>
#include <string>

namespace ocean_muduo
{

    /// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
    ///
    /// @code
    /// +-------------------+------------------+------------------+
    /// | prependable bytes |  readable bytes  |  writable bytes  |
    /// |                   |     (CONTENT)    |                  |
    /// +-------------------+------------------+------------------+
    /// |                   |                  |                  |
    /// 0      <=      readerIndex   <=   writerIndex    <=     size
    /// @endcode

    // 网络库底层的缓冲器类型定义
    class buffer
    {
    public:
        static const size_t k_cheap_prepend = 8;
        static const size_t k_initial_size = 1024;

        explicit buffer(size_t initial_size = k_initial_size);
        ~buffer();

        size_t readable_bytes() const;
        size_t writable_bytes() const;
        size_t prependable_bytes() const;

        // 返回缓冲区中 可读数据的起始地址
        const char *peek() const;

        // onMessage , 将char 转换为string
        void retrieve(size_t len);

        void retrieve_all();

        std::string retrieve_asstring(size_t len);

        // 把onMessage 函数上报的buffer数据，转换为std::string类型的数据返回
        std::string retrieve_all_asstring();

        // buffer_.size() -writer_index_ 属于可写区域的长度
        // 确认有足够的可写空间
        void ensure_writable_bytes(size_t len);

        // 把[data,data+len]内存上的数据，添加到buffer_的 writable缓冲区当中
        void append(const char *data, size_t len);

        char *begin_write();
        const char *begin_write() const;

        // 从fd上读取数据
        size_t read_fd(int fd, int *save_errno);
        // 通过fd发送数据
        ssize_t write_fd(int fd, int *save_errno);

    private:
        std::vector<char> buffer_;
        size_t reader_index_;
        size_t writer_index_;

        char *begin();

        const char *begin() const;

        void make_space(size_t len);
    };

} // namespace ocean_muduo
