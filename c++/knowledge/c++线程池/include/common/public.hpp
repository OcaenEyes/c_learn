/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-29 09:33:23
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-29 15:13:12
 * @FilePath: /c++/knowledge/c++线程池/include/common/public.hpp
 * @Description: 注释信息
 */

#include <memory>
#include <condition_variable>
#include <mutex>

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
    // 构造函数 , 可以让Any类型 接受其他任意类型的数据
    template <typename T>
    Any(T value) : pBase_(std::make_unique<Derived<T>>(value)) {}

    // 把Any对象里存储的data数据提取出来
    template <typename T>
    T cast_()
    {
        // 基类指针指向派生类对象 【将Base基类指针转为Derived派生类指针】
        return static_cast<Derived<T> *>(pBase_.get())->data_;
    }

    Any()
    {
    }
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

// 实现一个信号量类
class Semaphore
{
private:
    int res_limit_;
    std::mutex mtx_;
    std::condition_variable cond_;

public:
    Semaphore(int res_limit = 0) : res_limit_(res_limit) {}
    ~Semaphore() {}

    // 获取一个信号量资源
    void wait()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待带信号量有资源，没有资源的话，会阻塞当前线程
        cond_.wait(lock, [&]() -> bool
                   { return res_limit_ > 0; });
        res_limit_--;
    }
    // 增加一个信号量资源
    void post()
    {
        std::lock_guard<std::mutex> lock(mtx_);
        res_limit_++;
        cond_.notify_all();
    }
};

class Task; // Task类型的前置声明
// 实现接收  提交到线程池的task任务 在执行完成后的返回值 类型Result
class Result
{
private:
    Any any_;                    // 存储任务的返回值
    Semaphore sem_;              // 信号量,用于线程通信
    std::shared_ptr<Task> task_; // 指向对应获取返回值的 任务对象
    std::atomic_bool is_valid_;  // 原子变量, 用于判断任务返回值是否有效

public:
    Result(std::shared_ptr<Task> task, bool is_valid = true) : task_(task), is_valid_(is_valid) {}

    ~Result() {}

    // set_val方法， 获取任务执行完的返回值, task->run()之后 把run的返回值 通过set_val 存入any_
    void set_val(Any &&val)
    {
        any_ = std::move(val);
        sem_.post(); // 执行完任务，通知信号量，增加一个资源
    }

    // get方法，用户调用这个方法 获取task的返回值
    Any get()
    {
        if (!is_valid_)
        {
            return "";
        }

        sem_.wait(); // 等待信号量, task任务如果没有执行完，这里会阻塞用户的线程
        return std::move(any_);
    }
};