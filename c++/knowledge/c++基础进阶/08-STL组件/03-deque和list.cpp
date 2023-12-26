

/**
 * deque 双端队列容器
 *      #define MAP_SIZE 2
 *      #define QUE_SIZE 4096/sizeof(T)
 *    例如：
 *      deque<int> deq;
 *      4097 / sizeof(int) = 1024;
 *  底层数据结构： 动态开辟的二维数组， 一维数组从2开始， 以2倍的方式进行扩容， 第2维是固定长度的数组空间
 *               每次扩容后原来的二维数组，从新的第一维数组的下标oldsize/2开始存放， 上下都预留相同的空行，方便支持deque的首尾元素添加
 *               【每一个二维是连续的】
 *
 *  deque<int> deq;
 *
 *  增加：
 *      deq.push_back(20); // 从末尾添加元素 O(1)
 *      deq.push_front(20); // 从首部添加元素 O(1)
 *      deq.inset(it,20); // 在迭代器it指向的位置插入元素 O(n)
 *
 *  删除：
 *      deq.pop_back(); // 从尾部删除 O(1)
 *      deq.pop_front(); //从首部删除 O(1)
 *      deq.erase(it); // 删除 迭代器it指向的位置的元素 O(n)
 *
 *  查询：
 *      iterator迭代器查询； 连续的insert、erase 一定要考虑迭代器失效问题
 *
 *
 * list 链表容器
 *  底层数据结构：双向的循环链表  pre data next
 *
 *  list<int> mylist;
 *
 *  增加：
 *      mylist.push_back(20); // 从末尾添加元素 O(1)
 *      mylist.push_front(20); // 从首部添加元素 O(1)
 *      mylist.inset(it,20); // 在迭代器it指向的位置插入元素 O(1); 不涉及链表移动； 但插入时需要先进行查询操作，链表查询效率较低
 *
 *  删除：
 *      mylist.pop_back(); // 从尾部删除 O(1)
 *      mylist.pop_front(); //从首部删除 O(1)
 *      mylist.erase(it); // 删除 迭代器it指向的位置的元素 O(1); 不涉及链表移动； 但插入时需要先进行查询操作，链表查询效率较低
 *
 *  查询：
 *      iterator迭代器查询； 连续的insert、erase 一定要考虑迭代器失效问题
 *
 */

#include <iostream>
#include <deque>
#include <list>
#include <vector>

int main()
{
    return 0;
}