#include <iostream>

/**
 * 类模板
 *
 *
 */

template <typename T>
class SeqStack // 模板名称+参数列表 = 类名称
{
private:
    T *_pstack;
    int _top;
    int _size;

    void expand() // 顺序栈底层数组 按2倍的方式扩容
    {
        T *ptemp = new T[_size * 2];
        for (int i = 0; i < _top; i++)
        {
            ptemp[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = ptemp;
        _size *= 2;
    }

public:
    SeqStack<T>(int size = 10)
        : _pstack(new T[size]), _top(0), _size(size)
    {
    }

    ~SeqStack<T>()
    {
        delete[] _pstack;
        _pstack == nullptr;
    }

    SeqStack<T>(const SeqStack<T> &stack) // 拷贝构造
        : _top(stack._top), _size(stack._size)
    {
        _pstack = new T[_size];
        // 不要使用memcopy
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
    }

    SeqStack<T> &operator=(const SeqStack<T> &stack) // 赋值
    {
        // 防止自赋值
        if (this == &stack)
        {
            return *this;
        }

        delete[] _pstack;
        _top = stack._top;
        _size = stack._size;
        _pstack = new T[_size];
        for (int i = 0; i < _top; i++)
        {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }

    void push(const T &val); // 压栈

    void pop() // 出栈
    {
        if (empty())
        {
            return;
        }
        --_top;
    }

    T top() const // 返回栈顶元素
    {
        if (empty())
        {
            throw "stack is empty!"; // 抛出异常，也代表函数逻辑结束了
        }

        bool _pstack[_top - 1];
    }
    bool full() const
    { // 栈满
        return _top == _size;
    }
    bool empty() const
    { // 栈空
        return _top == 0;
    }
};

template <typename T>
void SeqStack<T>::push(const T &val)
{
    if (full())
    {
        expand();
    }
    _pstack[_top++] = val;
}

int main()
{
    SeqStack<int> intstack;
    intstack.push(19);
    intstack.push(29);
    intstack.pop();
    return 0;
}