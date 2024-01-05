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
    // 创建结构体数组
    struct Student stuArr[3] = {
        {"gzy", 25, 100},
        {"zy", 25, 100},
        {"g", 25, 100}};

    // 遍历结构体数组
    for (int i = 0; i < 3; i++)
    {
        cout << stuArr[i].name << "\n";
    }

    return 0;
}