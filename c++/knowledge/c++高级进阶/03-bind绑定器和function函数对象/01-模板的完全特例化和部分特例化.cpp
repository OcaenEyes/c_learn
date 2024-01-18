
#include <iostream>
#include <string.h>

// 模板的完全特例化和 非完全特例化

template <typename T>
bool compare(T a, T b)
{
    std::cout << "原始compare\n";
    return a > b;
}

template <> // 模板的特例化， 为 compare("aaa", "bbb"); 提供处理方法
bool compare<const char *>(const char *a, const char *b)
{
    std::cout << "为const char *特例化的compare\n";
    return strcmp(a, b) > 0;
}

template <typename T> // 原模板
class Vector
{
public:
    Vector() { std::cout << "Vector 原始模板构造!\n"; }
};

template <> // 为char* 提供的完全特例化版本
class Vector<char *>
{
public:
    Vector() { std::cout << "Vector 为char* 提供的完全特例化版本!\n"; }
};

template <typename PTR> // 针对指针类型提供的部分特例化版本
class Vector<PTR *>
{
public:
    Vector() { std::cout << "Vector 为指针类型 提供的部分特例化版本!\n"; }
};

//  针对函数指针 （有返回值， 有两个形参）提供部分特例化
template <typename R, typename A, typename B>
class Vector<R (*)(A, B)>
{
public:
    Vector() { std::cout << "Vector  为R (*)(A, B)为  函数指针类型 提供的部分特例化版本!\n"; }
};

int main()
{
    compare(10, 20);
    compare("aaa", "bbb");

    Vector<int> vec1;
    Vector<char *> vec2; // 有char*完全特例化 就优先使用char*完全特例化
    Vector<int *> vec3;  // 有部分特例化 就使用部分特例化
    Vector<int (*)(int, int)> vec4;
    return 0;
}