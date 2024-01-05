// 存储一个固定大小的相同类型元素的顺序集合
// 所有的数组都是由连续的内存位置组成。最低的地址对应第一个元素，最高的地址对应最后一个元素。


/*

概念	描述
多维数组	C++ 支持多维数组。多维数组最简单的形式是二维数组。
指向数组的指针	您可以通过指定不带索引的数组名称来生成一个指向数组中第一个元素的指针。
传递数组给函数	您可以通过指定不带索引的数组名称来给函数传递一个指向数组的指针。
从函数返回数组	C++ 允许从函数返回数组。

*/
//声明数组
/*
type arrayName [ arraySize ];
double balance[10];
*/

//初始化数组
/*
double balance[5] = {1000.0, 2.0, 3.4, 7.0, 50.0};
*/

// 访问数组元素

#include <iostream>
using namespace std;

#include <iomanip>
using std::setw;

int main()
{
    int n[10];

    for (int i = 0; i < 10; i++)
    {
        /* code */
        n[i] = i + 100;
    }
    cout << n << endl;
    for(int j : n)
    {
        cout << j << endl;
    }
}
