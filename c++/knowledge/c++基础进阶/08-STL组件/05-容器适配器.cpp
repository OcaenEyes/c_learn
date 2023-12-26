

/**
 * 标准容器 --  容器适配器
 *  1.适配器 底层没有自己的数据结构，它是另外一个容器的封装，它的方法全部由底层依赖的容器进行实现
 *  2.没有实现自己的迭代器
 *  3.
 *
 *
 *
 *
 *     譬如：
 *          template <typename T, typename Container = std::deque<T>>
 *           class Stack
 *           {
 *           private:
 *               Container con;
 *
 *           public:
 *               Stack<T, Container>()
 *               {
 *                   std::cout << "Stack<T, Container>()" << std::endl;
 *               }
 *               ~Stack<T, Container>()
 *               {
 *                   std::cout << "~Stack<T, Container>()" << std::endl;
 *               }
 *
 *              void push(const T &value)
 *              {
 *                  con.push_back(value);
 *              }
 *              void pop()
 *              {
 *                   con.pop_back();
 *              }
 *
 *              T top()
 *              {
 *                   return con.back();
 *              }
 *           };
 *
 *
 *
 * stack:  push入栈   pop出栈【先进后出】    top()查看栈顶元素   empty()判断栈是否空  size()元素个数
 *      stack底层依赖deque
 *
 * queue:  push入队   pop出队【先进先出】    front()查看队首元素    back()查看队尾元素   empty()判断栈是否空  size()元素个数
 *      queue底层依赖deque
 *
 *    stack和queue使用deque的原因：
 *      1.vector的初始内存效率太低，没有deque效率高
 *      2.deque尾部插入，头部删除效率比 vector好
 *      3.vector需要大片的连续内存， deque只需要分段的内存； 当存储大量数据时deque对内存的使用效率高
 *
 *
 * priority_queue:  push入队   pop出队【高优先级的先出队】 top()查看队顶元素  empty()判断队是否空   size()元素个数
 *       priority_queue底层依赖vector
 *
 *    priority_queue使用vector的原因：
 *      1.priority_queue底层默认把数据组成一个大根堆，在一个内存连续的数组上构建一个大根堆 或 小根堆
 * 
 *
 *
 *
 */

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <stack>

int main()
{
    std::cout << "\n===============stack=================\n";
    // push入栈   pop出栈    top查看栈顶元素   empty()判断栈是否空  size()元素个数
    std::stack<int> s;
    for (int i = 0; i < 20; i++)
    {
        s.push(i);
    }

    std::cout << "s.size:" << s.size() << std::endl;

    while (!s.empty())
    {
        std::cout << "s.top:" << s.top() << std::endl;
        s.pop();
    }
    std::cout << "\n===============queue=================\n";
    std::queue<int> q;
    for (int i = 0; i < 20; i++)
    {
        q.push(i);
    }

    std::cout << "q.size:" << q.size() << std::endl;
    while (!q.empty())
    {
        std::cout << "q.front:" << q.front() << std::endl;
        q.pop();
    }

    std::cout << "\n==============priority_queue==================\n";
    std::priority_queue<int> pq; // 优先级队列
    for (int i = 0; i < 20; i++)
    {
        pq.push(i);
    }
    std::cout << "pq.size:" << pq.size() << std::endl;
    while (!pq.empty())
    {
        std::cout << "pq.top:" << pq.top() << std::endl;
        pq.pop();
    }

    std::cout << "\n==============list==================\n";
    std::list<int> l;
    for (int i = 0; i < 20; i++)
    {
        l.push_back(i);
    }
    std::cout << "l.size:" << l.size() << std::endl;
    while (!l.empty())
    {
        std::cout << "l.front:" << l.front() << std::endl;
        l.pop_front();
    }
    std::cout << "\n===============deque=================\n";
    std::deque<int> d;
    for (int i = 0; i < 20; i++)
    {
        d.push_back(i);
    }
    std::cout << "d.size:" << d.size() << std::endl;
    while (!d.empty())
    {
        std::cout << "d.front:" << d.front() << std::endl;
        d.pop_front();
    }
    std::cout << "\n===============vector=================\n";
    std::vector<int> v;
    for (int i = 0; i < 20; i++)
    {
        v.push_back(i);
    }
    std::cout << "v.size:" << v.size() << std::endl;
    while (!v.empty())
    {
        std::cout << "v.front:" << v.front() << std::endl;
        v.erase(v.begin());
    }
    std::cout << "\n================================\n";

    return 0;
}