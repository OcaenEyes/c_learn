#include <iostream>
#include <vector>

/**
 * 容器的迭代器
 *
 *  const_iterator: 常量正向迭代器
 *    1.可查询迭代器指向的值, 但不能改
 *    const_iterator基类  <== iterator派生类 ；
 *
 *  iterator:普通的正向迭代器
 *    1.可查询迭代器指向的值
 *    2.可修改迭代器指向的值
 *
 *  const_reverse_iterator: 常量反向迭代器
 *    1.可查询迭代器指向的值, 但不能改
 *    const_reverse_iterator基类 <== reverse_iterator派生类 ；
 *
 *  reverse_iterator:普通的反向迭代器
 *    1.可查询迭代器指向的值
 *    2.可修改迭代器指向的值
 *
 */

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 20; i++)
    {
        v.push_back(i);
    }
    std::cout << "\n============正向迭代器===========\n";
    // std::vector<int>::iterator  普通的正向迭代器
    auto it = v.begin();
    for (; it != v.end(); it++)
    {
        std::cout << *it << std::endl; // 查询值

        if (*it == 10)
        {
            *it = 100; // 修改值
        }
    }

    for (auto &&i : v)
    {
        std::cout << "element: " << i << std::endl; // 查询值
    }

    std::cout << "\n============反向迭代器===========\n";
    // std::vector<int>::reverse_iterator  普通的反向迭代器
    auto it1 = v.rbegin();
    for (; it1 != v.rend(); it1++)
    {
        std::cout << *it1 << std::endl; // 查询值
        if (*it1 == 15)
        {
            *it1 = 19;
        }
    }

    return 0;
}