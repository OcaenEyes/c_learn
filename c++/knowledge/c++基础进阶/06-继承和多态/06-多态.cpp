/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 08:54:45
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 11:48:10
 * @FilePath: /c++/knowledge/c++基础进阶/06-继承和多态/06-多态.cpp
 * @Description: 注释信息
 */

/**
 * 如何解释多态？
 *  1.静态（编辑时期）的多态：函数重载、模板（函数模板、类模板）
 *    1)  bool compare(int,int){}
 *        bool compare(double,double){}
 *
 *          在编译阶段就确定好调用的函数版本
 *          compare(20,20);
 *          compare(2.5,4.5);
 *
 *
 *     2) template<typename T>
 *        bool compare(T a,T b){}
 *
 *          在编译阶段实例化一个对应的函数
 *          compare<int>(20,20);   ==> 实例化一个compare<int>
 *          compare<double>(2.5,4.5); ===> 实例化一个compare<double>
 *
 *  2.动态（运行时期）的多态：
 *    在继承结构中，基类指针（引用） 指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数）
 *    1）基类指针指向哪个派生类，就会调用哪个派生类的对象的覆盖方法 -->成为多态
 *       pbase->show();
 *    2）多态底层是通过动态绑定来实现的,pbase ->> 访问的是谁的vfptr -->>> 就会继续访问谁的vftable ===>>>> 于是调用的就是对应派生类对象的方法
 *
 *
 *
 *  软件设计六大原则
 *      1）单一职责原则（Single Responsibility Principle）：应该有且仅有一个原因引起类的变更
 *      2）开闭原则（Open Closed Principle）：对修改关闭，对扩展开放
 *      3）里氏替换原则（Liskov Substitution Principle）：
 *          -  1. 子类必须完全实现父类的方法
 *          -  2. 孩子类可以有自己的个性
 *          -  3. 覆盖或实现父类的方法时，输入参数可以被放大
 *          -  4. 覆盖或实现父类的方法时，输出结果可以被缩小
 *      4）迪米特法则（Law of Demeter），又叫“最少知道法则”
 *      5）接口隔离原则（Interface Segregation Principle）：
 *          -  客户端不应该依赖它不需要的接口，或者说类间的依赖关系应该建立在最小的接口上
 *      6）依赖倒置原则（Dependence Inversion Principle）
 *          -  1）每个类尽量都有接口或抽象类，或者接口和抽象类两者都具备
 *          -  2）变量的表面类型尽量是接口或抽象类
 *          -  3）任何类都不应该从具体类派生
 *          -  4）尽量不要重写基类的方法。如果基类是一个抽象类，而且这个方法已经实现了，子类尽量不要重写。
 *          -  5）结合里氏替换原则使用
 *
 * 
 *  继承的好处？
 *   1.可以做代码的复用
 *   2.可以在基类中给所有的派生类增加虚函数，在派生类重写，既可实现多态
 *
 */

#include <iostream>
#include <string>

class Animal
{
private:
protected:
    std::string _name;

public:
    Animal(std::string name) : _name(name)
    {
        std::cout << "Animal constructor" << std::endl;
    }

    ~Animal()
    {
        std::cout << "Animal  destructor" << std::endl;
    }

    virtual void bark() { std::cout << "Animal bark" << std::endl; }
};

class Cat : public Animal
{
private:
public:
    Cat(std::string name) : Animal(name)
    {
        std::cout << "Cat constructor" << std::endl;
    }

    ~Cat()
    {
        std::cout << "Cat  destructor" << std::endl;
    }

    void bark() override // 覆盖基类的bark函数
    {
        std::cout << "Cat bark" << std::endl;
    }
};

class Dog : public Animal
{
private:
public:
    Dog(std::string name) : Animal(name)
    {
        std::cout << "Dog constructor" << std::endl;
    }
    ~Dog()
    {
        std::cout << "Dog  destructor" << std::endl;
    }

    void bark() override // 覆盖基类的bark函数
    {
        std::cout << "Dog bark" << std::endl;
    }
};

class Pig : public Animal
{
private:
public:
    Pig(std::string name) : Animal(name)
    {
        std::cout << "Pig constructor" << std::endl;
    }
    ~Pig()
    {
        std::cout << "Pig destructor" << std::endl;
    }

    void bark() override // 覆盖基类的bark函数
    {
        std::cout << "Pig bark" << std::endl;
    }
};

void eat(Animal *animal)
{
    std::cout << "Eat" << std::endl;
    animal->bark(); // 动态绑定， 会调用对应的虚函数
}

int main()
{
    Cat cat("猫");
    Dog dog("狗");
    Pig pig("猪");
    cat.bark();
    dog.bark();
    pig.bark();
    std::cout << "----------------------" << std::endl;

    eat(&cat);
    eat(&dog);
    eat(&pig);
    std::cout << "----------------------" << std::endl;

    return 0;
}