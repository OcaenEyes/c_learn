/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 07:54:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 08:02:59
 * @FilePath: /c++/knowledge/入门到实战/chapter_08_指针和引用/输出引用.cpp
 * @Description: 注释信息
 */
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int a;
    int &ref_a = a;

    a = 100;
    cout << "a " << a << endl;
    cout << "ref_a" << ref_a << endl;

    a = 2;
    cout << "a " << a << endl;
    cout << "ref_a" << ref_a << endl;

    int b = 19;
    ref_a = b;
    cout << "a " << a << endl;
    cout << "ref_a" << ref_a << endl;

    ref_a--;
    cout << "a " << a << endl;
    cout << "ref_a" << ref_a << endl;

    return 0;
}