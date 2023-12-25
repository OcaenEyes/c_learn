
#include <iostream>

/**
 * 运算符重载： 成员方法、全局方法
 * 内存池、进程池、线程池、连接池、对象池
 */

template <typename T>
class Queue
{
public:
    Queue<T>() : _head(nullptr), _tail(nullptr)
    {
        _head = _tail = new QueueItem();
    }

    ~Queue<T>()
    {
        QueueItem *cur = _head;
        while (cur != nullptr)
        {
            _head = _head->_next;
            delete cur;
            cur = _head;
        }
    }

    // 入队操作
    void push(const T &t)
    {
        QueueItem *item = new QueueItem(t);
        _tail->_next = item; // 队尾的next指向item
        _tail = item;        // 将队尾指向item
    }

    // 出队操作
    void pop()
    {
        if (empty())
        {
            return;
        }
        QueueItem *item = _head->_next;
        _head->_next = item->_next;

        if (_head->_next == nullptr)
        {
            _tail = _head;
        }

        delete item;
    }

    T head() const
    {
        return _head->_next->_data;
    }

    T tail() const {}

    bool empty() const
    {
        return _head == _tail;
    }

private:
    // 考虑生成一个QueueItem的对象池； 譬如10000个QueueItem节点
    struct QueueItem
    {
        QueueItem(T t = T()) : _data(t), _next(nullptr){};
        // 给QueueItem提供自定义内存管理
        void *static operator new(size_t size)
        {
            if (_itemPool == nullptr)
            {
                _itemPool = (QueueItem *)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
                QueueItem *p = _itemPool;
                for (; p < _itemPool + POOL_ITEM_SIZE - 1; p++)
                {
                    p->_next = p + 1;
                }
                p->_next = nullptr;
            }
            QueueItem *p = _itemPool;
            _itemPool = _itemPool->_next;
            return p;
        }

        static operator delete(void *p)
        {
            QueueItem *q = (QueueItem *)p;
            q->_next = _itemPool; // 指向连接池的第一个节点
            _itemPool = q;        // itempool重新指向到最前面的q
        }

        T _data;
        QueueItem *_next;
        static QueueItem *_itemPool;
        static const int POOL_ITEM_SIZE = 10000;
    };

    QueueItem *_head; // 对头
    QueueItem *_tail; // 对尾
};

template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

int main()
{

    Queue<int> que;
    for (int i = 0; i < 10000; i++)
    {
        que.push(i);
        que.pop();
    }
    std::cout << que.empty() << std::endl;

    return 0;
}