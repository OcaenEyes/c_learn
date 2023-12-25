/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-25 12:01:17
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-25 12:01:17
 * @FilePath: /c++/knowledge/c++基础进阶/06-继承和多态/08-抽象类.cpp
 * @Description: 注释信息
 */

/**
 * 抽象类和普通类的区别：
 *
 *
 *
 *
 * 一般把什么类设计为抽象类？
 *
 *
 *
 *
 */

#include <iostream>
#include <string>

// 动物基类， 泛指    类---> 抽象一个实体的类型

/**
 * 定义Animal的初衷，不是让Animal抽象某个实体的类型
 *  1.std::string _name; 让所有的动物实体类， 通过继承Animal直接复用该属性
 *  2.给所有的派生类保留统一的覆盖/重写接口
 *
 *
 *
 * 拥有纯属函数的类叫做 抽象类；
 *   抽象类不能在实例化对象，但是可以定义指针和引用变量
 *
 */
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

    virtual void bark() = 0; // 纯虚函数， 抽象函数， 没有实现， 子类必须实现
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

// 汽车基类
class Car // 抽象类
{
public:
    Car(std::string name) : _name(name) {}
    double getLeftMiles(double oil)
    {
        return oil * getMilesPerGallon();
    }

    std::string getName() const {
        return  _name;
    }

protected:
    std::string _name;
    virtual double getMilesPerGallon() = 0; // 纯虚函数
};

class Benz : public Car
{
public:
    Benz(std::string name) : Car(name) {}
    double getMilesPerGallon() override
    {
        return 20;
    }
};

class BMW : public Car
{
public:
    BMW(std::string name) : Car(name) {}
    double getMilesPerGallon() override
    {
        return 30;
    }
};

class Audi : public Car
{
public:
    Audi(std::string name) : Car(name) {}
    double getMilesPerGallon() override
    {
        return 40;
    }
};

double showCarLeftMiles(Car *car, double oil){
    std::cout << "Car name is " << car->getName() << std::endl;
    std::cout << "Left miles is " << car->getLeftMiles(oil) << std::endl;
    return car->getLeftMiles(oil);
}

void eat(Animal *animal)
{
    std::cout << "Eat" << std::endl;
    animal->bark(); // 动态绑定， 会调用对应的虚函数
}

int main()
{
    Benz benz("benz");
    BMW bmw("bmw");
    Audi audi("audi");
    showCarLeftMiles(&benz, 10);
    showCarLeftMiles(&bmw, 10);
    showCarLeftMiles(&audi, 10);

    return 0;
}