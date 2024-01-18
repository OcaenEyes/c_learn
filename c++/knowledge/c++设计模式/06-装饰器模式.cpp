
#include <iostream>
#include <memory>

/**
 * 装饰器： 增加现有类的功能；  但是增加现有类的功能，还有一个方法就是使用 新增一个子类
 *
 * 装饰器模式： Decorator，增加现有类的功能
 *
 */

class Car
{
public:
    virtual void show() = 0;
};

class BMW : public Car
{
public:
    void show()
    {
        std::cout << "一个宝马汽车，配置有： 基本配置\n";
    }
};

class Benz : public Car
{
public:
    void show()
    {
        std::cout << "一个奔驰汽车，配置有： 基本配置\n";
    }
};

class Audi : public Car
{
public:
    void show()
    {
        std::cout << "一个奥迪汽车，配置有： 基本配置\n";
    }
};

// 装饰器的基类
class CarDecorator : public Car
{
public:
    CarDecorator(Car *p) : p_car(p) {}

private:
    Car *p_car;
};

// 装饰器1, 定速巡航
class ConcreateDecorator01 : public Car
{
public:
    ConcreateDecorator01(Car *p) : p_car(p) {}
    void show()
    {
        p_car->show();
        std::cout << "定速巡航功能！\n";
    }

private:
    Car *p_car;
};

class ConcreateDecorator02 : public Car
{
public:
    ConcreateDecorator02(Car *p) : p_car(p) {}
    void show()
    {
        p_car->show();
        std::cout << "座椅加热功能！\n";
    }

private:
    Car *p_car;
};

class ConcreateDecorator03 : public Car
{
public:
    ConcreateDecorator03(Car *p) : p_car(p) {}
    void show()
    {
        p_car->show();
        std::cout << "自动刹车功能！\n";
    }

private:
    Car *p_car;
};

int main()
{

    Car *p1 = new ConcreateDecorator01(new BMW());
    Car *p2 = new ConcreateDecorator02(new Benz());
    Car *p3 = new ConcreateDecorator03(new Audi());

    p1->show();
    delete p1;
    p1 = nullptr;

    p2->show();
    delete p2;
    p2 = nullptr;

    p3->show();
    delete p3;
    p3 = nullptr;
    return 0;
}