#include <map>
#include <functional>
#include <algorithm>
#include <ctime>
#include <iostream>

void hello1()
{
    std::cout << "hello!\n";
}

void hello2(std::string str)
{
    std::cout << str << "\n";
}

int sum(int a, int b)
{
    return a + b;
}

class Test
{
public:
    Test() {}
    void hello1()
    {
        std::cout << "Test::hello!\n";
    }

    void hello2(std::string str)
    {
        std::cout << "Test::hello with str!" << str << " \n";
    }
};

int main()
{
    // 从function的类模板定义处，看到希望用一个函数类型来实例化function
    std::function<void()> func1 = hello1;
    func1();

    std::function<void(std::string)> func2 = hello2;
    func2("hello,gzy");

    std::function<int(int, int)> func3 = sum;
    std::cout << func3(3, 6) << "\n";

    Test a;

    std::function<void(Test *)> func4 = &Test::hello1;
    func4(&a);
    std::function<void(Test *, std::string)> func5 = &Test::hello2;
    func5(&a, "call &Test::hello2");

    return 0;
}