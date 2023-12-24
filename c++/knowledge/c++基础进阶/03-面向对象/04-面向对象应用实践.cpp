/**
 * @file 04-面向对象应用实践.cpp
 * @author OCEANGZY(you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */

// 浅拷贝、深拷贝构造函数 和赋值重载函数
// String类
// 循环队列 Queue

#include <string.h>

class String
{
private:
    char *m_data; // 用于保存字符串
public:
    String(const char *str = nullptr) // 普通构造函数
    {
        if (str != nullptr)
        {
            m_data = new char[strlen(str) + 1];
            strcpy(this->m_data, str);
        }
        else
        {
            m_data = new char[1];
            *m_data = '\0';
        }
    }

    String(const String &str) // 拷贝构造函数
    {
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
    }

    String &operator=(const String &str) // 赋值重载函数
    {
        if (this == &str)
        {
            return *this;
        }
        delete[] m_data;
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
        return *this;
    }

    ~String() // 析构函数
    {
        delete[] m_data;
    }
};

class Queue
{
private:
    int *_pQue; // 申请队列的数组空间
    int _front; // 指示对头的位置
    int _rear;  // 指示队尾的位置
    int _size;  // 队列扩容的总大小

public:
    Queue(int size = 20)
    {
        _pQue = new int[size];
        _front = 0;
        _rear = 0;
        _size = size;
    }

    ~Queue()
    {
        delete[] _pQue;
        _pQue = nullptr;
    }

    void addQue(int val)
    {
       
         
    }
};

int main()
{

    String str1;
    String str2("hello"); // 普通构造
    String str3 = "world";

    str1 = str2; // 赋值重载 【左右两边对象都已经存在】

    String str4 = str3; // 拷贝构造
    String str5(str3);  // 拷贝构造

    return 0;
}