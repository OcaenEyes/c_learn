#include <iostream>
#include <string>

/**
 * string 类型的迭代器iterator
 */

int main()
{
    std::string s = "hello";
    for (std::string::iterator it = s.begin(); it != s.end(); ++it)
    {
        // 迭代器可以透明的访问，容器内部的元素的值
        std::cout << *it << std::endl; // 迭代器的解引用
    }
    return 0;
}