/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 15:08:25
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-15 07:36:43
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/find_high_score.cpp
 * @Description: 注释信息
 */

/**
 * 找出最高分
 * 定义学生类：包括名字、学号、成绩等几项属性， 并实现成员函数来比较成绩
 * 输入学生信息，输出分数最高学生的成绩
 */
#ifndef FIND_HIFH_SCORE_H
#define FIND_HIFH_SCORE_H
#include <cstring>
#include <iostream>

class Student
{
private:
    /* data */

public:
    Student(/* args */);
    ~Student();
    char name[20];
    int score;
    int num;
    int compare(float max);
};

Student::Student(/* args */)
{
    this->score = 0;
    this->num = 0;
    strcpy(this->name, "null");
}

int Student::compare(float max)
{
    if (score > max)
    {
        return 1;
    }
    else if (score == max)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

Student::~Student()
{
}

#endif

int main(int argc, char *argv[])
{
    int n = 0;
    do
    {
        printf("请输入学生人数（1-30之间）\n");
        scanf("%d", &n);
    } while (!n > 0 || n > 30);

    // 创建学生类数组
    Student *pstudents = new Student[n];

    printf("请按照学号、成绩、姓名的 顺序的个数输入学生的信息：\n");
    for (int i = 0; i < n; i++)
    {
        /* code */
        printf("请输入第%d个学生的信息：\n", i + 1);
        scanf("%d,%d,%s", &pstudents[i].num, &pstudents[i].score, pstudents[i].name);
    }

    Student *max_pstudent = new Student[1];

    int max_score = 0; // 学生中的最高分数
    int max_count = 1; // 最高成绩人数
    // 将最高成绩学生放入记录数组

    for (int i = 0; i < n; i++)
    {
        switch (pstudents[i].compare(max_score))
        {
        case 1:
        {
            max_score = pstudents[i].score;
            // 刷新最高成绩学生信息
            max_count = 1;
            if (max_pstudent != NULL)
            {
                delete[] max_pstudent;
            }
            max_pstudent = new Student[1];
            max_pstudent[0] = pstudents[i];
        }
        break;
        case 2:
        {
            // 将成绩最高的数据保存起来
            Student *ptemp = max_pstudent;
            // 刷线最高成绩
            max_pstudent = new Student[++max_count];

            // 将成绩最高者的数据 转移到新开辟的数组空间中， 新数组空间比原来的数组空间容量多1
            for (int j = 0; j < max_count - 1; j++)
            {
                max_pstudent[j] = ptemp[j];
            }
            max_pstudent[max_count - 1] = pstudents[i];
            // 回收内存
            delete[] ptemp;
        }
        break;
        default:
            break;
        }
    }

    // 输出成绩最高者信息
    printf("当前最高成绩为:%d,成绩最高者为:\n", max_score);
    for (int i = 0; i < max_count; i++)
    {
        printf("%d,%s,%d\n", max_pstudent[i].num, max_pstudent[i].name, max_pstudent[i].score);
    }

    // 回收内存
    delete[] pstudents;
    delete[] max_pstudent;
    return 0;
}