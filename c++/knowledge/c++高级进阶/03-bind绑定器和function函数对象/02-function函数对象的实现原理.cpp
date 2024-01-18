/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 07:19:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 07:39:19
 * @FilePath: /c++/knowledge/c++高级进阶/03-bind绑定器和function函数对象/02-function函数对象的实现原理.cpp
 * @Description: 注释信息
 */

#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>

void hello(std::string str)
{
    std::cout << str << "\n";
}

template <typename FTY>
class myfunction
{
};

template <typename R, typename A>
class myfunction<R(A)>
{
public:
    using PFUNC = R (*)(A);
    myfunction(PFUNC pfunc) : func_(pfunc) {}
    R operator()(A arg) // 小括号运算符 重载函数
    {
        return func_(arg);
    }

private:
    PFUNC func_;
};

int main()
{
    std::function<void(std::string)> func1 = hello;
    func1("hello");

    myfunction<void(std::string)> func2 = hello;
    func2("myfunction");

    return 0;
}