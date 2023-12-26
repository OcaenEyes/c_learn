#include <iostream>
#include <algorithm> //C++ STL的范型算法头文件
#include <vector>
#include <functional> // 包含函数对象 和绑定器

/**
 * 范型算法 template + 迭代器 + 函数对象
 *  特点：
 *    1）参数接收的都是迭代器
 *    2）参数还可以接收函数对象(c函数指针)
 *
 * 绑定器 + 二元函数对象 ===>  一元函数对象
 *  bind1st：把二元函数对象的operator()(a,b)的第一个形参a绑定起来
 *  bind2nd：把二元函数对象的operator()(a,b)的第二个形参b绑定起来
 *
 *
 *  1.sort：排序
 *  2.find
 *  3.find_if
 *  4.binary_search //二分查找
 *  5.for_each
 *
 */

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));

    for (auto &&i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::sort(vec.begin(), vec.end()); // 默认从小到大排序

    // 有序容器中 进行二分查找
    auto it = std::binary_search(vec.begin(), vec.end(), 10);
    if (it)
    {
        std::cout << "find 10 success\n"
                  << std::endl;
    }
    else
    {
        std::cout << "find 10 failed\n"
                  << std::endl;
    }

    // 传入指定的函数对象，调整sort的逻辑，譬如传入std::greater<int>() 变成了从大到小排序
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "std::greater<int>()排序后:";
    for (auto &&i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // find_if,按条件进行查询。需要一个一元函数对象
    // greater a>b
    // less a<b
    // 把50插入到vector容器当中， 找第一个小于50的数字； bind1st把50绑定到greater的第一个形参；   bind1st把50绑定到less的第二个形参
    // 找到了则返回对应的迭代器位置，找不到则返回end()
    //[](int val)-> bool{return val <48;};
    auto it2 = std::find_if(vec.begin(), vec.end(),
                            std::bind1st(std::greater<int>(), 50));
    // 与上面的绑定器效果一致
    // auto it2 = std::find_if(vec.begin(), vec.end(),
    //                         [](int val) -> bool
    //                         { return val < 48; });

    vec.insert(it2, 50);
    std::cout << "\nstd::find_if(),进行插入50之后:";
    for (auto &&i : vec)
    {
        std::cout << i << " ";
    }

    std::for_each(vec.begin(), vec.end(), [](int &val)
                  { val++; });
    std::cout << "\nstd::for_each(),对vector容器中的元素进行自增之后:";
    for (auto &&i : vec)
    {
        std::cout << i << " ";
    }

    return 0;
}