#include <iostream>
#include <string>
using namespace std;

// 创建学生数据类型
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
} s3;

int main()
{
    // 创建具体学生
    // 方式一
    struct Student s1;
    s1.name = "gzy";
    s1.age = 25;
    s1.score = 100;

    // 方式2
    struct Student s2 = {"gzy1", 25, 120};

    return 0;
}
