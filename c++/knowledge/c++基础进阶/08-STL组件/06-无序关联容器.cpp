/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 06:37:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-26 07:20:43
 * @FilePath: /c++/knowledge/c++基础进阶/08-STL组件/06-关联容器.cpp
 * @Description: 注释信息
 */

#include <queue> // queue 和 priority_queue
#include <vector>
// 有序关联容器头文件
#include <set> // set 和 multiset
#include <map> // map 和 multimap
// 无序关联容器文件
#include <unordered_map> // unordered_set 和 unordered_multiset
#include <unordered_set> // unordered_map 和 unordered_multimap

#include <iostream>

/**
 * 关联容器：
 *  1.各个容器底层的数据结构
 *  2.常用增删查方法
 *      增加：insert(val)
 *      遍历：iterator搜索，调用find成员方法, foreach
 *      删除：erase(key) ， erase(it)
 *
 *  map的operator[key]
 *   1.查询
 *   2.如果key不存在，会插入一对数据[key,value默认值]
 */

int main()
{
    std::cout << "\n==============unordered_set=======================\n";
    std::unordered_set<int> uset; // 不会存储key值重复的元素
    for (int i = 0; i < 50; i++)
    {
        uset.insert(i); // 插入位置由哈希表的算法控制
    }

    std::cout << "uset size: " << uset.size() << std::endl;
    std::cout << "uset count: " << uset.count(10) << std::endl;
    std::unordered_set<int>::iterator it = uset.find(10);
    if (it != uset.end())
    {
        std::cout << "uset find: " << *it << std::endl;
    }

    uset.erase(10); // 按key删除元素
    std::cout << "uset size: " << uset.size() << std::endl;

    for (it = uset.begin(); it != uset.end(); it++)
    {
        if (*it == 25)
        {
            it = uset.erase(it); // 按迭代器删除元素
        }
    }
    std::cout << "uset size: " << uset.size() << std::endl;

    it = uset.find(15);
    if (it != uset.end())
    {
        uset.erase(it); // 按迭代器删除元素
    }

    for (auto &&i : uset)
    {
        std::cout << "uset element: " << i << std::endl;
    }

    std::cout << "\n==============unordered_map=======================\n";
    /**
     * map [key,value]的pair;
     *      first; ==>key
     *      second; ==>value
     */
    std::unordered_map<int, std::string> umap; // 不允许键key重复
    umap.insert(std::make_pair(1, "one"));     // 打包成pair对象再插入map中
    umap.insert(std::make_pair(2, "two"));
    umap.insert(std::make_pair(3, "three"));
    umap.insert({4, "four"});

    std::cout << "umap size: " << umap.size() << std::endl;
    std::cout << "umap count: " << umap.count(1) << std::endl;
    std::cout << "umap[key]:umap[1]: " << umap[1] << std::endl;

    umap.erase(1); // 按key删除元素

    umap[2] = "new two";  // 修改元素
    umap[5] = "add five"; // 修改元素

    auto it1 = umap.find(2); // 查找元素，返回迭代器
    if (it1 != umap.end())
    {
        std::cout << "umap element: " << it1->first << ":" << it1->second << std::endl;
        umap.erase(it1); // 按迭代器删除元素
    }

    for (auto &&i : umap)
    {
        std::cout << "umap element: " << i.first << ":" << i.second << std::endl;
    }

    const int ARR_LEN = 100000;
    int arr[ARR_LEN] = {0};
    for (int i = 0; i < ARR_LEN; i++)
    {
        arr[i] = rand() % 10000 + 1;
    }
    std::cout << "\n==============处理海量数据查重=======================\n";
    // 上面10W个整数，统计哪些数字重复了，并统计重复次数
    std::unordered_map<int, int> umap2;
    for (auto &&i : arr)
    {
        // auto it = umap2.find(i);
        // if (it == umap2.end())
        // {
        //     umap2.insert(std::make_pair(i, 1));
        // }
        // else
        // {
        //     it->second += 1;
        // }
        umap2[i]++; // 与上面的逻辑等价
    }

    for (auto &&i : umap2)
    {
        if (i.second > 1)
        {
            std::cout << "repeat number: " << i.first << " repeat count:" << i.second << std::endl;
        }
    }
    std::cout << "\n==============处理海量数据去重=======================\n";

    std::unordered_set<int> uset1;
    for (auto &&i : arr)
    {
        uset1.insert(i); // 无序单重集合 去重
    }
    for (auto &&i : uset1)
    {
        std::cout << "uset1 element: " << i << std::endl;
    }

    return 0;
}