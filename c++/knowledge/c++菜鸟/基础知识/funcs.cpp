#include <iostream>
using namespace std;

// 函数声明
/*
return_type function_name( parameter list );
*/


// 函数定义
/*
return_type function_name( parameter list )
{
   body of the function
}

返回类型：一个函数可以返回一个值。return_type 是函数返回的值的数据类型。有些函数执行所需的操作而不返回值，在这种情况下，return_type 是关键字 void。
函数名称：这是函数的实际名称。函数名和参数列表一起构成了函数签名。
参数：参数就像是占位符。当函数被调用时，您向参数传递一个值，这个值被称为实际参数。参数列表包括函数参数的类型、顺序、数量。参数是可选的，也就是说，函数可能不包含参数。
函数主体：函数主体包含一组定义函数执行任务的语句。
*/

// 函数调用
/*
调用类型	描述
传值调用	该方法把参数的实际值赋值给函数的形式参数。在这种情况下，修改函数内的形式参数对实际参数没有影响。
指针调用	该方法把参数的地址赋值给形式参数。在函数内，该地址用于访问调用中要用到的实际参数。这意味着，修改形式参数会影响实际参数。
引用调用	该方法把参数的引用赋值给形式参数。在函数内，该引用用于访问调用中要用到的实际参数。这意味着，修改形式参数会影响实际参数。
默认情况下，C++ 使用传值调用来传递参数
*/

/*---------分割线--------*/



int maxnum(int num1, int num2);
int minnum(int num1, int num2);
int maxnum1(int,int);

int main(){
   int a = 10;
   int b = 2;
   int res;

   res= maxnum(a,b);
   cout << res <<'\n';
   return 0;
}


int maxnum(int num1,int num2){
   int result;
   if(num1 > num2){
      result = num1;
   }else{
      result = num2;
   }
   return result;
}


// lambda函数与表达式
/*
把函数看作对象。Lambda 表达式可以像对象一样使用，比如可以将它们赋给变量和作为参数传递，还可以像函数一样对其求值
[capture](parameters)->return-type{body}
*/
