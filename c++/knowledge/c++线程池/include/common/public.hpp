/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-29 09:33:23
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-29 09:57:52
 * @FilePath: /c++/knowledge/c++线程池/include/common/public.hpp
 * @Description: 注释信息
 */

#include <memory>

// Any类型：可以接受任意数据的类型
class Any
{
private:
    // 基类类型
    class Base
    {
    public:
        virtual ~Base() {} // 析构函数 变为虚函数， 当基类指针/引用 指向派生类对象时，才可以让派生类对象析构函数触发
    };

    // 派生类类型
    template <typename T>
    class Derived : public Base
    {
    public:
        Derived(T value) : data_(value) {}
        ~Derived() {}

    private:
        T data_;
    };

public:
    template <typename T>
    Any(T value) : pBase_(new Derived<T>(value)) {}
    Any() {}
    ~Any() {}

    // 禁用拷贝构造
    Any(const Any &) = delete;
    // 禁用赋值重载
    Any &operator=(const Any &) = delete;

    // 允许右值引用 拷贝构造， 移动构造

    // 移动构造函数的构造函数类型。通过使用移动构造函数，我们可以在进行对象复制时直接“窃取”拷贝对象所保有的一些资源，比如已经在原对象中分配的堆内存，文件描述符，IO流等。通常我们在声明移动构造函数时，都会使用 noexcept 关键字来修饰
    /**
     * "noexcept"关键字 表示它修饰的函数不会在执行过程中抛出异常。 通常使用两种不同的方式来使用这个关键字。
     * 第一种方式是将noexcept放在函数声明的后面：
            void except_func() noexcept
            这样这个函数就会被标记为不会抛出异常。
     * 第二种方式是为noexcept提供一个常量表达式作为参数，如果这个常量表达式的值为true，那么函数就会被标记为不会抛出异常。
            constexpr bool suppressExcept = true;
            void except_func() noexcept (suppressExcept);
            与通常我们使用try...catch结构来捕获异常所不同的是，使用noexcept关键字标记的函数在它抛出异常时，编译器会直接调用名为"std::terminate"的方法，来中断程序的执行，因此某种程度上可以有效阻止异常的传播和扩散。
     *
     */
    Any(Any &&other) noexcept : pBase_(std::move(other.pBase_)) {}

    // 允许右值引用 赋值重载， 移动构造
    Any &operator=(Any &&other) noexcept
    {
        pBase_ = std::move(other.pBase_);
        return *this;
    }

private:
    // 定一个一个基类指针
    std::unique_ptr<Base> pBase_;
};
