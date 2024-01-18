#include <iostream>
#include <string>
#include <memory>

/**
 * 简单工厂  simple factory
 *      优点：把对象的创建，封装在一个接口函数里面，通过传入不同的标识，返回创建的对象
 *          客户不用自己负责new对象，不用了解对象创建的详细过程
 *      缺点：提供创建对象实例的接口函数不闭合，不能对修改关闭
 *
 * 工厂方法  factory method
 *      优点：Factory基类， 提供一个纯虚函数（创建产品）， 定义派生类（具体产品的工厂）负责创建对应的产品，
 *          可以做到不同的产品，在不同的工厂里创建； 能对现有产品、工厂的修改关闭
 *      缺点：很多产品有关联关系，属于一个类簇， 不应该放在不同工厂生产【会导致工厂过多】
 *
 * 抽象工厂  abstract factory
 *      优点： 把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂abstract factory里，  派生类（具体的产品工程）
 *
 *
 *  工厂模式，主要是封装了对象的创建
 *
 *
 *
 *  Software entities like classes,modules and functions should be open for extension but closed for modifications
 一个软件实体, 如类, 模块, 函数等应该对扩展开放, 对修改封闭.
 *
 */

// 系列产品1
class Car
{
public:
    Car(std::string name) : name_(name) {}
    virtual void show() = 0;

protected:
    std::string name_;
};

class BMW : public Car
{
public:
    BMW(std::string name) : Car(name) {}
    void show()
    {
        std::cout << "一辆宝马汽车" << name_ << "\n";
    }
};

class Benz : public Car
{
public:
    Benz(std::string name) : Car(name) {}
    void show()
    {
        std::cout << "一辆奔驰汽车" << name_ << "\n";
    }
};

class Audi : public Car
{
public:
    Audi(std::string name) : Car(name) {}
    void show()
    {
        std::cout << "一辆奥迪汽车" << name_ << "\n";
    }
};

// 系列产品2
class Light
{
    virtual void bright() = 0;
};

class BMWLight : public Light
{
    void bright()
    {
        std::cout << "BMW light bright!\n";
    }
};
class AudiLight : public Light
{
    void bright()
    {
        std::cout << "Audi light bright!\n";
    }
};

enum CarType
{
    CT_BMW,
    CT_Audi,
    CT_Benz
};
class SimpleFactory // 简单工厂模式
{
public:
    Car *create_car(CarType ct)
    {
        switch (ct)
        {
        case CT_BMW:
            return new BMW("X1");
            break;
        case CT_Benz:
            return new Benz("X1");
            break;
        case CT_Audi:
            return new Audi("X1");
            break;

        default:
            std::cout << "传入工厂的参数不正确!\n";
            break;
        }
        return nullptr;
    }
};

// 工厂方法
class Factory
{
public:
    virtual Car *create_car(std::string name) = 0;
};

// 宝马工厂
class BMWFactory : public Factory
{
public:
    Car *create_car(std::string name)
    {
        return new BMW(name);
    }
};

// 奥迪工厂
class AudiFactory : public Factory
{
public:
    Car *create_car(std::string name)
    {
        return new Audi(name);
    }
};

/// 把有关联关系的产品簇，提供产品对象的统一创建
class AbstractFactory
{
public:
    virtual Car *create_car(std::string name) = 0;
    virtual Light *create_carlight() = 0;
};

// 宝马工厂
class NewBMWFactory : public AbstractFactory
{
public:
    Car *create_car(std::string name)
    {
        return new BMW(name);
    }
    Light *create_carlight()
    {
        return new BMWLight();
    }
};

// 奥迪工厂
class NewAudiFactory : public AbstractFactory
{
public:
    Car *create_car(std::string name)
    {
        return new Audi(name);
    }
    Light *create_carlight()
    {
        return new AudiLight();
    }
};

int main()
{
    // Car *p1 = new BMW("X1");
    // Car *p2 = new Benz("C");
    // Car *p3 = new Audi("A6");

    // 简单工厂
    SimpleFactory *factory = new SimpleFactory();
    Car *p1 = factory->create_car(CT_BMW);
    Car *p2 = factory->create_car(CT_Benz);
    Car *p3 = factory->create_car(CT_Audi);

    p1->show();
    p2->show();
    p3->show();

    delete factory;
    factory = nullptr;
    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
    delete p3;
    p3 = nullptr;

    // 简单工厂 + 智能指针
    std::unique_ptr<SimpleFactory> fc(new SimpleFactory());
    std::unique_ptr<Car> p4(fc->create_car(CT_Audi));
    p4->show();

    // 工厂方法+ 智能指针

    std::unique_ptr<Factory> bmwfc(new BMWFactory());
    std::unique_ptr<Car> p5(bmwfc->create_car("bmwfc"));
    p5->show();

    std::unique_ptr<Factory> audifc(new AudiFactory());
    std::unique_ptr<Car> p6(audifc->create_car("audifc"));
    p6->show();

    return 0;
}