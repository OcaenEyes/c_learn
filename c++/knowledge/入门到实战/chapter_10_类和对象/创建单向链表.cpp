/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-15 23:21:27
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-16 00:03:00
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/创建单向链表.cpp
 * @Description: 注释信息
 */

#include <iostream>
class Node
{
private:
    /* data */
    int data;
    Node *next;

public:
    Node(/* args */);
    ~Node();

    // 构造方法创建离散节点
    Node(int _data)
    {
        data = _data;
        next = NULL;
    }
    static Node *phead; // 链表头
    static Node *ptail; // 链表尾

    // 向链表尾部加入节点
    static void addNode(int _data)
    {
        if (phead == NULL)
        {
            /* code */
            phead = new Node(_data);
            ptail = phead;
            return;
        }
        ptail->next = new Node(_data);
        ptail = ptail->next;
    }

    static void addNode(Node *_node)
    {
        if (phead == NULL)
        {
            phead = _node;
            ptail = phead;
            return;
        }
        ptail->next = _node;
        ptail = ptail->next;
    }

    // 根据数据内容删除结点
    static bool deleteNodes(int _data)
    {
        bool flag = false;
        if (phead == NULL)
        {
            return flag;
        }

        // 遍历链表查找 符合条件的结点
        Node *ptemp = phead;
        if (phead->data == _data)
        {
            ptemp = phead->next;
            delete phead;
            phead = ptemp;
        }
        
        
    }
};

Node::Node(/* args */)
{
}

Node::~Node()
{
}
