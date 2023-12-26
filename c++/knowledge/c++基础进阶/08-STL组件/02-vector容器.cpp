/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 02:47:08
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-26 03:35:39
 * @FilePath: /c++/knowledge/c++基础进阶/08-STL组件/02-vector容器.cpp
 * @Description: 注释信息
 */

/**
 * vector 向量容器
 *  底层数据结果： 动态开辟的数组，【内存是连续的】每次以原来空间大小的2倍进行扩容 [空间配置器allocate 、 deallocate 、construct 、 destroy ]
 *
 *  std::vector<int> vec;
 *
 *  增加：
 *      vec.push_back(20); 末尾添加元素20,O(1) , 可能导致容器扩容
 *      vec.insert(it,20);  在it迭代器指向的位置，插入一个元素20, O(n) , 可能导致容器扩容
 *
 *  删除：
 *      vec.pop_back();   末尾删除元素,O(1)
 *      vec.erase(it);    删除迭代器it指向位置的元素, O(n)
 *
 *  查询：
 *      operator[] 下标的随机访问,    vec[5];      O(1)
 *      iterator迭代器遍历 [通用推荐]
 *      find
 *      for_each
 *      foreach===>底层通过iterator迭代器遍历来实现
 *
 *  注意：对容器进行连续插入 或 删除操作（insert / erase），一定要更新迭代器，否则第一次（insert / erase）完成以后，迭代器就失效了
 *
 *  常用方法：
 *      size();   返回容器有效元素的个数
 *      empty();  判断是否为空
 *      reserve(20); vector预留空间； 只给容器开辟指定大小的空间，不添加元素
 *      resize(20); 容器扩容用的；不见给容器开辟指定大小的空间，还会添加新的元素，添加了20个0
 *      swap  两个容器的元素交换
 *
 *
 */

#include <iostream>
#include <vector>

int main()
{

    std::vector<int> vec;

    vec.reserve(20); // 容器预留空间，避免容器频繁扩容

    for (int i = 0; i < 20; i++)
    {
        vec.push_back(i);
    }

    int size = vec.size();
    std::cout << "删除所有的偶数前：\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    auto it1 = vec.begin(); // 容器第一个元素
    for (; it1 != vec.end(); it1++)
    {
        std::cout << *it1 << " "; // 迭代器解引用
    }

    std::cout << std::endl;

    // 把容器中所有的偶数删除
    auto it2 = vec.begin();
    while (it2 != vec.end())
    {
        if (*it2 % 2 == 0)
        {
            it2 = vec.erase(it2); // 删除迭代器it2指向的元素； 通过erase()的返回值，更新it2, 解决迭代器失效问题
        }
        else
        {
            it2++;
        }
    }
    std::cout << "删除所有的偶数后：\n";
    it1 = vec.begin(); // 容器第一个元素
    for (; it1 != vec.end(); it1++)
    {
        std::cout << *it1 << " "; // 迭代器解引用
    }
    std::cout << std::endl;

    // 给vector容器中，所有奇数前插入一个比奇数 小于1的偶数
    for (it1 = vec.begin(); it1 != vec.end(); it1++)
    {
        if (*it1 % 2 != 0)
        {
            it1 = vec.insert(it1, *it1 - 1);
            it1++;
        }
    }
    std::cout << "在奇数前插入偶数：\n";
    for (it1 = vec.begin(); it1 != vec.end(); it1++)
    {
        std::cout << *it1 << " "; // 迭代器解引用
    }
    std::cout << std::endl;

    return 0;
}