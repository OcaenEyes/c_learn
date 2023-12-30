
#include "../include/common/public.hpp"
#include "../include/threadpool.h"

Result::Result(std::shared_ptr<Task> task, bool is_valid) : task_(task), is_valid_(is_valid)
{
    std::cout << " Result(std::shared_ptr<Task> task, bool is_valid = true)\n";
    task_->set_result(this);
}

// 拷贝构造
Result::Result(const Result &other) : task_(other.task_)
{
    std::cout << " Result(const Result &other)\n";
    if (other.is_valid_)
    {
        is_valid_ = true;
    }
    else
    {
        is_valid_ = false;
    }
}

// 拷贝赋值运算符
Result &Result::operator=(const Result &other)
{
    std::cout << " Result &operator=(const Result &other)\n";
    task_ = other.task_;
    // 注意这里不能直接将other.is_valid_赋值给is_valid_
    if (other.is_valid_)
    {
        is_valid_ = true;
    }
    else
    {
        is_valid_ = false;
    }
    return *this;
}

// 移动构造函数
Result::Result(Result &&other) noexcept : task_(std::move(other.task_))
{
    std::cout << "Result(Result &&other) noexcept \n";
    if (other.is_valid_)
    {
        is_valid_ = true;
    }
    else
    {
        is_valid_ = false;
    }
}

// 移动赋值运算符
Result &Result::operator=(Result &&other) noexcept
{
    std::cout << "Result &operator=(Result &&other) noexcept\n";
    if (this != &other)
    {
        task_ = std::move(other.task_);
        if (other.is_valid_)
        {
            is_valid_ = true;
        }
        else
        {
            is_valid_ = false;
        }
    }
    return *this;
}