#include <iostream>
using namespace std;

/*
    - 模拟自动取款机
    - 主要功能：
        - 用户输入密码登录主界面
        - 取款功能
        - 取款后显示取款余额、剩余余额
        - 退出功能
    - 要实现的界面包括：
        - 输入正确密码进入主目录界面
        - 执行取款界面
        - 显示取款金额和剩余金额界面
        - 退出系统界面

*/

int main()
{
    char Key, CMoney;
    int password, password1 = 123, i = 1, a = 1000;

    while (1)
    {
        /* code */

        do
        {
            system("cls");
            printf("*******************\n");
            printf("* 请选择一个菜单 *\n");
            printf("* 1.输入密码    *\n");
            printf("* 2.取款       *\n");
            printf("* 3.退出       *\n");
            printf("*******************\n");
            Key = getchar();
        } while (Key != '1' && Key != '2' && Key != '3');

        switch (Key)
        {
        case '1':
            /* code */
            system("clear");
            do
            {
                /* code */
                printf(" 请输入密码 \n");
                scanf("%d", &password);
                if (password1 != password)
                {
                    /* code */
                    i++;
                    if (i > 3)
                    {
                        printf("错误，按任意键退出 \n");
                        getchar();
                        exit(0);
                    }
                    else
                    {
                        puts("错误，请重试");
                    }
                }

            } while (password1 != password && i <= 3);
            printf("验证通过，按任意键继续\n");
            getchar();

        case '2':
            do
            {
                system("clear");
                if (password != password1)
                {
                    printf("请验证密码后再试，按任意键继续\n");
                    getchar();
                    break;
                }
                else
                {
                    printf("*******************\n");
                    printf("* 请选择要取款的金额 *\n");
                    printf("* 1.100元    *\n");
                    printf("* 2.200元       *\n");
                    printf("* 3.300元      *\n");
                    printf("* 4.返回      *\n");
                    printf("*******************\n");
                    CMoney = getchar();
                }
            } while (CMoney != '1' && CMoney != '2' && CMoney != '3' && CMoney != '4');

            switch (CMoney)
            {
            case '1':
                /* code */
                a = a - 100;
                printf("*******************\n");
                printf("* 您已取款100元*\n");
                printf("* 余额为 %d    *\n", a);
                printf("* 按任意键返回      *\n");
                printf("*******************\n");
                getchar();
                break;

            case '2':
                /* code */
                a = a - 200;
                printf("*******************\n");
                printf("* 您已取款200元*\n");
                printf("* 余额为 %d    *\n", a);
                printf("* 按任意键返回      *\n");
                printf("*******************\n");
                getchar();
                break;
            case '3':
                /* code */
                a = a - 300;
                printf("*******************\n");
                printf("* 您已取款300元*\n");
                printf("* 余额为 %d    *\n", a);
                printf("* 按任意键返回      *\n");
                printf("*******************\n");
                getchar();
                break;
            case '4':
                /* code */
                break;
            default:
                break;
            }
            // break;
        case '3':
            printf("*******************\n");
            printf("* 感谢您的使用！*\n");
            printf("*   拜拜！    *\n");
            printf("*******************\n");
            getchar();
            break;

            // default:
            //     break;
        }
        break;
    }
    return 0;
}