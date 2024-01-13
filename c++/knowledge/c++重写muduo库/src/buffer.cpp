/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-10 07:36:48
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-13 09:35:56
 * @FilePath: /c++/knowledge/c++重写muduo库/src/buffer.cpp
 * @Description: 注释信息
 */
#include "buffer.h"

#include <errno.h>
// #include <bits/types/struct_iovec.h>
#include <sys/uio.h>
#include <unistd.h>

namespace ocean_muduo
{
    buffer::buffer(size_t initial_size)
        : buffer_(k_cheap_prepend + k_initial_size),
          reader_index_(k_cheap_prepend),
          writer_index_(k_cheap_prepend)
    {
    }

    buffer::~buffer()
    {
    }

    size_t buffer::readable_bytes() const
    {
        return writer_index_ - reader_index_;
    }

    size_t buffer::writable_bytes() const
    {
        return buffer_.size() - writer_index_;
    }

    size_t buffer::prependable_bytes() const
    {
        return reader_index_;
    }

    const char *buffer::peek() const
    {
        return begin() + reader_index_;
    }

    void buffer::retrieve(size_t len)
    {
        if (len < readable_bytes()) // 说明只读取了len长度的内容，
        {
            reader_index_ += len; // 还剩下 reader_index_ += len -writer_index_ 的内容没有读
        }
        else
        {
            retrieve_all();
        }
    }

    void buffer::retrieve_all()
    {
        reader_index_ = writer_index_ = k_cheap_prepend;
    }

    std::string buffer::retrieve_asstring(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len); // 上面一句把缓冲区可读的数据，已经读取出来， 对缓冲区进行复位操作
        return result;
    }

    // 把on_message函数上报的Buffer数据，转成string类型的数据返回
    std::string buffer::retrieve_all_asstring()
    {
        return retrieve_asstring(readable_bytes()); // 应用可读取的数据
    }

    void buffer::ensure_writable_bytes(size_t len)
    {
        if (writable_bytes() < len)
        {
            make_space(len); // 扩容函数
        }
    }

    void buffer::append(const char *data, size_t len)
    {
        ensure_writable_bytes(len);
        std::copy(data, data + len, begin_write());
        writer_index_ += len;
    }

    char *buffer::begin_write()
    {
        return begin() + writer_index_;
    }

    const char *buffer::begin_write() const
    {
        return begin() + writer_index_;
    }

    size_t buffer::read_fd(int fd, int *save_errno)
    {
        char extrabuf[65536] = {0}; // 栈上的内存空间 64k
        iovec vec[2];
        const size_t writable = writable_bytes(); // buffer_缓冲区 剩余的可写区域大小
        vec[0].iov_base = begin() + writer_index_;
        vec[0].iov_len = writable;

        vec[1].iov_base = extrabuf;
        vec[1].iov_len = sizeof(extrabuf);

        const int iovcnt = (writable < sizeof(extrabuf)) ? 2 : 1;
        const ssize_t n = ::readv(fd, vec, iovcnt);
        if (n < 0)
        {
            *save_errno = errno;
        }
        else if (n <= writable)
        {
            writer_index_ += n;
        }
        else
        { // extrabuf 也写入了数据
            writer_index_ = buffer_.size();
            append(extrabuf, n - writable); // writer_index_开始写， 写n- writable大小的数据
        }

        return n;
    }

    ssize_t buffer::write_fd(int fd, int *save_errno)
    {
        ssize_t n = ::write(fd, peek(), readable_bytes());
        if (n < 0)
        {
            *save_errno = errno;
        }
        return n;
    }

    char *buffer::begin()
    {
        // it.operator*()运算符重载函数
        // *解引用， &再取址
        return &*buffer_.begin(); // 取vector首元素的地址， 也就是vector的首地址
    }

    // 从fd上读取数据， poller工作在LT模式
    // buffer_缓冲区是有大小的，但是从fd上读数据的时候，不知道tcp数据最终的大小
    const char *buffer::begin() const
    {
        return &*buffer_.begin();
    }

    // 当前：k_cheap_prepend | reader | writer
    // 实际数据：k_cheap_prepend ｜ len |
    void buffer::make_space(size_t len)
    {
        if (writable_bytes() + prependable_bytes() < len + k_cheap_prepend)
        { // 当实际可写区域+空闲区域 仍小于len + k_cheap_prepend
            buffer_.resize(writer_index_ + len);
        }
        else
        { // 重新分配区域
            std::copy(
                begin() + reader_index_,
                begin() + writer_index_,
                begin() + k_cheap_prepend);
            reader_index_ = k_cheap_prepend;
            writer_index_ = reader_index_ + readable_bytes();
        }
    }

} // namespace ocean_muduo
