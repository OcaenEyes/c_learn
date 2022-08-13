<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-11 23:57:43
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-13 00:47:48
 * @FilePath: /c++/practices/c++11and14/readme.md
 * @Description: 注释信息
-->
https://labfile.oss.aliyuncs.com/courses/605/1.zip
https://labfile.oss.aliyuncs.com/courses/605/2.zip
https://labfile.oss.aliyuncs.com/courses/605/3.zip
https://labfile.oss.aliyuncs.com/courses/605/4.zip
https://labfile.oss.aliyuncs.com/courses/605/5.zip
https://labfile.oss.aliyuncs.com/courses/605/6.zip
https://labfile.oss.aliyuncs.com/courses/605/7.zip
https://labfile.oss.aliyuncs.com/courses/605/8.zip


```
 #include<iostream>
 using namespace std;
 int add(int *a,int *b){
     int s;
     s = *a + *b;
     cout<<"sig1  "<<a<<endl;//a就是指针，它是一个地址；
     cout<<"sig2  "<<&a<<endl;//&a,&在这里仍然是个取址的符号，取得是地址的地址；
     cout<<"sig3  "<<*&a<<endl;//这里我觉得“*”就是将地址所指的内容给呈现出来，所以这里就是a；
     cout<<"sig4  "<<**&a<<endl;//同上，继续将a作为地址的内存上的内容读出来；
     return s;
 } 
 int main(){
     int sum,a=1,b=2;
     sum=add(&a,&b);//为什么要用&a，在这里“&a”传的是地址，因为add的参数是指针，指针要指向地址；
     cout<<"sig5  "<<&a<<endl;//它还是第13行中定义的那个a，所以跟第6行显示的一样；
     cout<<sum<<endl;//两个值相加返回的就是int型的值啦；
     int *p=&a;
     cout<<p<<endl;//将a的地址赋给指针p；
     cout<<*p<<endl;//将p所指向的地址的内容呈现；
     int &c=a;//在这里是引用，之前看一篇博文上写的一句话特别好“&在类型后边时是引用，和变量在一起不挨着类型是是取址。”
     cout<<c<<endl;//所以这里a就是c，是内存中的同一块。
     return 0;
  } 
```