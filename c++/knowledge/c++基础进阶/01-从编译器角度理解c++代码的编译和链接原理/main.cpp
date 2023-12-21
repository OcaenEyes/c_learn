// 引用sum.cpp文件里面定义的全局变量  以及函数
extern int gdata;  // gdata *UND*
int sum(int, int); // sum *UND*

int data = 20; // data .data数据段
int main()     // main .text函数代码段
{
    int a = gdata;
    int b = data;

    int ret = sum(a, b);
    return 0;
}