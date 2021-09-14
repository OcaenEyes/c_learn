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
    do
    {
        system("cls");
        printf("*******************\n");
        printf("* 请选择一个菜单 *");
        printf("* 1.输入密码    *");
        printf("* 2.取款       *");
        printf("* 3.退出       *");

    } while (Key != '1' && Key != '2' && Key != '3');

    switch (Key)
    {
    case '1':
        /* code */
        break;
    case '2':
        /* code */
        break;
    case '3':
        /* code */
        break;

    default:
        break;
    }
    return 0;
}