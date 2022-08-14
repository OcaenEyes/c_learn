/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 21:38:10
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 21:42:47
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/命名空间.cpp
 * @Description: 注释信息
 */
#include <iostream>

namespace testname
{
    int ii = 10;
} // namespace testname

int main()
{
    std::cout << testname::ii << std::endl;
    return 0;
}