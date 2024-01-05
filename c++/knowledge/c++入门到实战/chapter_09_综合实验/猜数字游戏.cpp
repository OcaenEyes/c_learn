/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 08:15:49
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 09:45:18
 * @FilePath: /c++/knowledge/入门到实战/chapter_09_综合实验/猜数字游戏.cpp
 * @Description: 注释信息
 */

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

void guess(int n)
{
    printf("开始调用初始化数字～");
    int acount, bcount, i, j, k = 0, flag, a[10], b[10];
    do
    {
        flag = 0;
        srand((unsigned)time(NULL)); // 使用系统时钟设定随机种子

        for (i = 0; i < n; i++)
        {
            a[i] = rand() % 10; // 每次产出0-9范围内任意的一个随机数， 并存到数组a中
        }
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (a[i] = a[j]) // 判断数组a中是否有 相同的数字
                {
                    flag = 1;
                    break; // 如果相同则 标识位1
                }
            }
        }

    } while (flag == 1); // 若标识位1， 则重新分配数据
    do
    {
        k++;        // 记录猜数字的次数
        acount = 0; // 每次猜的过程中位置和数字 都正确的个数
        bcount = 0; // 每次猜的过程中位置不正确，但数字正确的个数
        printf("猜一下吧:");
        for (i = 0; i < n; i++)
        {
            scanf("%d", &b[i]); // 输入猜测的数据保存到数组b中
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (a[i] == b[i])
                {
                    acount++;
                    break;
                }

                if (a[i] == b[j] && i != j)
                {
                    bcount++;
                    break;
                }
            }
        }

        printf("结果:%d A %d B\n\n", acount, bcount);

        if (acount == n) // 判断account是否与数字个数相同
        {
            if (k == 1)
            {
                printf("太棒啦！！！\n");
            }
            else if (k <= 5)
            {
                printf("你是个天才～\n");
            }
            else if (k <= 10)
            {
                printf("你真聪明～\n");
            }
            else
            {
                printf("你还需要继续努力～\n\n");
                getchar();
                printf("按任意键继续");
                getchar();
            }
            break;
        }

    } while (1);
}
int main(int argc, char *argv[])
{
    int i, j;
    while (1)
    {
        /* code */
        system("clear"); // 清屏
        printf("1.开始游戏\n");
        printf("2.游戏规则\n");
        printf("3.退出游戏\n");
        printf("选择\n");

        scanf("%d", &i);
        switch (i)
        {
        case 1: // 如果选择1 ，则开始游戏
            /* code */
            system("clear");
            printf("请输入使用数字个数:\n");
            scanf("%d", &j);
            guess(j);
            sleep(5);
            break;
        case 2: // 如果选择2 ，则展示游戏规则
            /* code */
            system("clear");
            printf("**游戏规则**\n");
            printf("step1: 输入初始化的数据维度\n");
            printf("step2: 输入数字，用空格分割\n");
            printf("step3: A 表示位置和数字都对");
            printf("\t B表示数字正确但位置不对\n");
            sleep(5);
            break;
        case 3: // 如果选择3 ，则退出游戏
            /* code */
            exit(0);
        default:
            break;
        }
    }

    return 0;
}