#include <iostream>
using namespace std;

/**
 * @brief
 * 输入学生的学号、及语文、数学、英语成绩，并输出学生各科成绩信息及平均成绩
 * @return int
 */
int main()
{
    int i, num;
    int chinese[50], math[50], english[50];
    long studentId[50];
    float aver[50];

    printf("请输入学生数量：\n");
    scanf("%d", &num);

    printf("请输入学生的学号 和三科成绩:\n");
    printf("student chinese math english \n");
    for (int i = 0; i < num; i++)
    {
        /* code */
        printf("Num.%d>", i + 1);
        scanf("%ld%d%d%d", &studentId[i], &chinese[i], &math[i], &english[i]);
        aver[i] = (float)(chinese[i] + math[i] + english[i]) / 3;
    }
    puts("\nstudentid chinese math english");
    for (int i = 0; i < num; i++)
    {
        /* code */
        printf("%8ld %8d %8d %8d %8.2f \n", studentId[i], chinese[i], math[i], english[i], aver[i]);
    }
    return 0;
}