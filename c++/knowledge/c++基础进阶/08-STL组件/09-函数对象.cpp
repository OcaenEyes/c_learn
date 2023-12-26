
/**
 *
 * 函数对象 ===>  c语言里面的函数指针
 *
 * c++的函数对象实现方案
 *    1.通过operator()小括号重载运算，可以省略函数的调用开销， 比通过函数指针调用函数效率高（函数指针调用函数 不能inline内联调用）
 *    2.由于函数对象是类生成的，所以可以添加相关的成员变量，用来记录函数调用时更多的信息
 *
 *
 *
 */

#include <iostream>

// template <typename T>
// bool compare(T a, T b)
// {
//     return a > b; // 不够灵活，不能动态的处理大于、小于、等于的操作
// }

// 使用c的函数指针解决方案
template <typename T>
bool greater(T a, T b)
{
    return a > b;
}

template <typename T>
bool equal(T a, T b)
{
    return a == b;
}

template <typename T>
bool less(T a, T b)
{
    return a < b;
}

// c函数指针实现
// compare是c++的库函数模板
template <typename T, typename Compare>
bool compare(T a, T b, Compare cmp) // 把compare函数指针传入
{
    return cmp(a, b); // 通过函数指针调用函数，是没有办法内联的，效率很低， 因为函数调用开销
}

/*======================================================*/

// c++的函数对象实现方案
/**
 * 1.通过operator()小括号重载运算，可以省略函数的调用开销， 比通过函数指针调用函数效率高（函数指针调用函数 不能inline内联调用）
 * 2.由于函数对象是类生成的，所以可以添加相关的成员变量，用来记录函数调用时更多的信息
 *
 */
template <typename T>
class mygreater // 函数对象，有operator()小括号重载运算
{
public:
    bool operator()(T a, T b) // 二元函数对象
    {
        return a > b;
    }
};

template <typename T>
class myless // 函数对象，有operator()小括号重载运算
{
public:
    bool operator()(T a, T b) // 二元函数对象
    {
        return a < b;
    }
};

template <typename T>
class myequal // 函数对象，有operator()小括号重载运算
{
public:
    bool operator()(T a, T b)
    {
        return a == b;
    }
};

int main()
{
    std::cout << "==========函数指针调用=========\n";
    std::cout << compare(1, 2, greater<int>) << std::endl;
    std::cout << compare(1.0, 2.0, less<int>) << std::endl;
    std::cout << compare("1", "2", equal<std::string>) << std::endl;

    std::cout << "==========函数对象-通过()重载调用=========\n";
    std::cout << compare(1, 2, mygreater<int>()) << std::endl;
    std::cout << compare(1.0, 2.0, myless<int>()) << std::endl;
    std::cout << compare("1", "2", myequal<std::string>()) << std::endl;

    return 0;
}