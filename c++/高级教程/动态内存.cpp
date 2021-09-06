// 栈：在函数内部声明的所有变量都将占用栈内存。
// 堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。
/*
    可以使用特殊的运算符为给定类型的变量在运行时分配堆内的内存，这会返回所分配的空间地址。这种运算符即 new 运算符。
    如果您不再需要动态分配的内存空间，可以使用 delete 运算符，删除之前由 new 运算符分配的内存。
*/

#include <iostream>
using namespace std;

int newdelete()
{
    double *pvalue = NULL; // 初始化为 null 的指针
    pvalue = new double;   // 为变量请求内存

    *pvalue = 29494.99; //在分配的地址存储值
    cout << "Value of pvalue :" << *pvalue << endl;

    delete pvalue; //释放内存

    return 0;
}

int twoV()
{
    int **p;
    int i, j; // p[4][8]
    //开始分配4行8列的二维数据
    p = new int *[4];
    for (i = 0; i < 4; i++)
    {
        /* code */
        p[i] = new int[8];
    }

    for (i = 0; i < 4; i++)
    {
        /* code */
        for (j = 0; j < 8; j++)
        {
            /* code */
            p[i][j] = j * i;
        }
    }

    cout << "二维数组是:"
         << "\n";
    cout << *p << "\n";

    // 打印数据
    for (i = 0; i < 4; i++)
    {
        /* code */
        for (j = 0; j < 8; j++)
        {
            /* code */
            if (j == 0)
                cout << "\n";
            cout << p[i][j] << "\t";
        }
    }

    //开始释放申请的堆
    for (i = 0; i < 4; i++)
    {
        delete[] p[i];
    }
    delete[] p;
    return 0;
}

int threeV()
{
    int i, j, k; // p[2][3][4]

    int ***p;
    p = new int **[2];
    for (i = 0; i < 2; i++)
    {
        p[i] = new int *[3];
        for (j = 0; j < 3; j++)
            p[i][j] = new int[4];
    }

    //输出 p[i][j][k] 三维数据
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 4; k++)
            {
                p[i][j][k] = i + j + k;
                cout << p[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // 释放内存
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            delete[] p[i][j];
        }
    }
    for (i = 0; i < 2; i++)
    {
        delete[] p[i];
    }
    delete[] p;

    return 0;
}

int main()
{

    // new 和 delete 运算符
    /*
        - new 和 delete运算符
        - new data-type;
        - 定义一个指向 double 类型的指针，然后请求内存，该内存在执行时被分配,可以按照下面的语句使用 new 运算符来完成这点
            - double* pvalue  = NULL; // 初始化为 null 的指针
            - pvalue  = new double;   // 为变量请求内存
            - delete pvalue;        // 释放 pvalue 所指向的内存
*/
    newdelete();
    // 数组的动态内存分配
    /*
        - 为一个字符数组（一个有 20 个字符的字符串）分配内存
            - char* pvalue  = NULL;   // 初始化为 null 的指针
            - pvalue  = new char[20]; // 为变量请求内存
            - delete [] pvalue;        // 删除 pvalue 所指向的数组

        - 一维数组
        - 动态分配,数组长度为 m
            - int *array=new int [m];
        - 释放内存
            - delete [] array;

        - 二维数组
            - int **array
            - 假定数组第一维长度为 m， 第二维长度为 n
            - 动态分配空间
            - array = new int *[m];
            - for( int i=0; i<m; i++ )
            - {
            -     array[i] = new int [n]  ;
            - }
            - //释放
            - for( int i=0; i<m; i++ )
            - {
            -     delete [] array[i];
            - }
            - delete [] array;


        - 三维数组
            - int ***array;
            - 假定数组第一维为 m， 第二维为 n， 第三维为h
            - 动态分配空间
            - array = new int **[m];
            - for( int i=0; i<m; i++ )
            - {
            -     array[i] = new int *[n];
            -     for( int j=0; j<n; j++ )
            -     {
            -         array[i][j] = new int [h];
            -     }
            - }
            - 释放
            - for( int i=0; i<m; i++ )
            - {
            -     for( int j=0; j<n; j++ )
            -     {
            -         delete[] array[i][j];
            -     }
            -     delete[] array[i];
            - }
            - delete[] array;
    */
    twoV();
    threeV();
    return 0;
}
