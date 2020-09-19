// 类定义
// class Box {
//     public:
//         double length;
//         double width;
//         double height;
// };

// 定义对象
// Box box1;
// Box box2;

/*
概念	描述
类成员函数	类的成员函数是指那些把定义和原型写在类定义内部的函数，就像类定义中的其他变量一样。
类访问修饰符	类成员可以被定义为 public、private 或 protected。默认情况下是定义为 private。
构造函数 & 析构函数	类的构造函数是一种特殊的函数，在创建一个新的对象时调用。类的析构函数也是一种特殊的函数，在删除所创建的对象时调用。
C++ 拷贝构造函数	拷贝构造函数，是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。
C++ 友元函数	友元函数可以访问类的 private 和 protected 成员。
C++ 内联函数	通过内联函数，编译器试图在调用函数的地方扩展函数体中的代码。
C++ 中的 this 指针	每个对象都有一个特殊的指针 this，它指向对象本身。
C++ 中指向类的指针	指向类的指针方式如同指向结构的指针。实际上，类可以看成是一个带有函数的结构。
C++ 类的静态成员	类的数据成员和函数成员都可以被声明为静态的。
*/

/*
  // public:
 
  // 公有成员
 
  // protected:
 
  // 受保护成员
 
  // private:
 
  // 私有成员

*/

#include <iostream>
using namespace std;

class Box
{
public:
    double length;
    double width;
    double height;
    // 类成员函数
    double getVolume(void)
    {
        return length * width * height;
    }
};

// 类构造函数 和析构函数
/*
类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。
构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。
构造函数可用于为某些成员变量设置初始值

类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。
析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。
析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源
*/

class Line
{
public:
    void setLength(double len);
    double getLength(void);
    Line();  // 这是构造函数声明
    ~Line(); // 这是析构函数声明

private:
    double length;
};

// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}

void Line::setLength(double len)
{
    length = len;
}

double Line::getLength(void)
{
    return length;
}

int main()
{
    // 声明box1
    Box box1;
    Box box2;

    //存储体积
    double volume = 0.0;

    // box1明细
    box1.height = 5.0;
    box1.width = 6.0;
    box1.length = 7.0;

    // box1明细
    box2.height = 15.0;
    box2.width = 16.0;
    box2.length = 17.0;

    volume = box1.height * box1.length * box1.width;
    cout << "box1体积" << volume << "\n";

    volume = box2.height * box2.length * box2.width;
    cout << "box2体积" << volume << "\n";

    return 0;
}
