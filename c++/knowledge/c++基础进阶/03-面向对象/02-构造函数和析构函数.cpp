/**
 * @file 02-构造函数和析构函数.cpp
 * @author OCEANGZY (you@domain.com)
 * @brief OOP实现一个顺序栈
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <iostream>

class SeqStack
{
private:
    int *_pstack; // 动态开辟数组， 存储顺序栈的元素
    int _size;    // 数组扩容的总大小
    int _top;     // 指向栈顶元素的位置

    void resize(int size = 10)
    {
        int *temp = new int[_size + size];
        for (int i = 1; i <= _top; i++)
        {
            temp[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = temp;
        _size += size;
    }

public:
    SeqStack(int size = 10); // 可以参数， 因此可提供多个构造函数
    ~SeqStack();             // 析构函数只有有一个

    void init(int size = 10)
    {
        _pstack = new int[size];
        _top = 1;
        _size = size;
    }

    void release()
    {
        delete[] _pstack;
        _pstack = nullptr;
    }

    void push(int val)
    {
        if (full())
        {
            resize();
        }
        _pstack[++_top] = val;
    }

    void pop()
    {
        if (empty())
        {
            return;
        }
        _top--;
    }

    int top()
    {
        return _pstack[_top];
    }

    bool empty()
    {
        return _top == 1; // 相等时为true
    }

    bool full()
    {
        return _top == _size - 1; // 相等时为true
    }

    // 自定义拷贝构造函数, 根据_size的长度自定义拷贝构造， 深拷贝
    SeqStack(const SeqStack &s)
    {
        std::cout << "SeqStack(const SeqStack &s)\n";
        _pstack = new int[s._size];
        _top = s._top;
        _size = s._size;
        for (int i = 1; i <= _top; i++)
        {
            _pstack[i] = s._pstack[i];
        }
    }

    // 赋值重载函数
    void operator=(const SeqStack &s)
    {
        std::cout << "operator=(const SeqStack &s)\n";
        // 防止自赋值
        if (this == &s)
        {
            return;
        }

        delete[] _pstack; // 需要先将当前对象占用的外部资源

        _pstack = new int[s._size];
        _top = s._top;
        _size = s._size;
        for (int i = 1; i <= _top; i++)
        {
            _pstack[i] = s._pstack[i];
        }
    }
};

SeqStack::SeqStack(int size)
{
    std::cout << "SeqStack()\n";
    _pstack = new int[size];
    _top = 1;
    _size = size;
}

SeqStack::~SeqStack()
{
    std::cout << "~SeqStack()\n";
    delete[] _pstack;
    _pstack = nullptr;
}

int main(int argc, char const *argv[])
{
    SeqStack s; // 开辟内存调用构造函数

    SeqStack s1 = s; // 对象的默认拷贝构造函数,【做内存的数据拷贝，如果对象占用外部资源，则浅拷贝会出现异常】 将s内存对应的数据 复制给s1内存； 那么s1析构的时候会导致_pstack指向的资源删除， 在s析构的时候就会出现野指针异常

    SeqStack s2(s); // 调用自定义的拷贝构造函数

    SeqStack s3;
    s3 = s; // 赋值操作，【做内存的数据赋值，把s1指向的资源 ，让s3也指向它】

    // s.init(20);  // 对象成员变量的初始化操作
    for (int i = 0; i < 15; i++)
    {
        s.push(rand() % 100);
    }

    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    // s.release(); // 释放对象成员变量占用的外部资源

    return 0;
}
