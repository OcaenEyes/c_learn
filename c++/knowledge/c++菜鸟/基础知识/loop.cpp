// 循环类型
/*
循环类型	描述
while 循环	当给定条件为真时，重复语句或语句组。它会在执行循环主体之前测试条件。
for 循环	多次执行一个语句序列，简化管理循环变量的代码。
do...while 循环	除了它是在循环主体结尾测试条件外，其他与 while 语句类似。
嵌套循环	您可以在 while、for 或 do..while 循环内使用一个或多个循环。
*/


// 循环控制语句
/*
控制语句	描述
break 语句	终止 loop 或 switch 语句，程序流将继续执行紧接着 loop 或 switch 的下一条语句。
continue 语句	引起循环跳过主体的剩余部分，立即重新开始测试条件。
goto 语句	将控制转移到被标记的语句。但是不建议在程序中使用 goto 语句。
*/

#include <iostream>
using namespace std;

int whileloop();
int forloop();
int forloop1();
int dowhileloop();

int main(){
    int i = whileloop();
    int j = forloop();
    int k = forloop1();
    int l = dowhileloop();
    system("pause");
    return 0;
}


int whileloop(){
    int x = 10;
    while (/* condition */ x<30)
    {
        /* code */
        cout << "whileloop x value is" << x << endl;
        x++;  
    }
    return x;
}


int forloop(){
    int x; 
    for (int i = 0; i < 20; i++)
    {
        /* code */
        x = i;
        cout << "forloop x value is " << x << '\n';
    }
    return x;
}

int forloop1(){
    int marray[5] = {1,2,3,4,5};
    int x;
    for (auto &&i : marray /* int &i : marray*/ /* auto &i : marray*/)
    {
         x = i*2;
         cout << x << '\n';
    }
    return x ;
}

int dowhileloop(){
    int x = 10;
    do
    {
        /* code */
        cout << "dowhileloop x value is " << x << endl;
        ++x;
    } while (/* condition */x <20 );
    return x;
}