#include <iostream>

using namespace std;

/**
 * @brief
 * 班级竞选班长，3个候选人， 输入参加选举的人数，及每个人选举的内容， 输出3个候选人最终的票数及无效选票数
 * @return int
 */
int main()
{
    int i, v0 = 0, v1 = 0, v2 = 0, v3 = 0, n, a[50];
    printf("请输入参加选举的人数:\n");
    scanf("%d", &n);
    printf("请输入每个人所选的人:\n");
    for (int i = 0; i < n; i++)
    {
        /* code */
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        /* code */
        switch (a[i])
        {
        case 1:
            v1++; /*选1号票*/
            break;
        case 2:
            v2++; /*选2号票*/
            break;
        case 3:
            v3++; /*选3号票*/
            break;
        default:
            v0++; /*无效票*/
        }
    }
    printf("最终选举结果:\n");
    printf("选举1号的：%d\n 选举2号的：%d\n 选举3号的：%d\n 无效票：%d\n", v1, v2, v3, v0);
    return 0;
}
