#include <iostream>
#include <string>
using namespace std;

// 定义结构体
struct Student
{
    /* data */
    // 成员列表
    //姓名
    string name;
    //年龄
    int age;
    //分数
    int score;
};

int main()
{
    // 创建结构体变量
    struct Student s = {"gzy",25,100};

    // 通过指针指向结构体变量
    struct Student * p = &s;
    cout << p << "\n";
    cout << &s << "\n";

    // 通过指针访问结构体变量
    cout << p->name <<"\n";

    return 0;
}