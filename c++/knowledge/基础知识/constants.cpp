#include <iostream>
// 常量
/*
整数常量
整数常量可以是十进制、八进制或十六进制的常量
前缀指定基数：0x 或 0X 表示十六进制，0 表示八进制，不带前缀则默认表示十进制
整数常量后缀是 U 和 L 的组合，U 表示无符号整数（unsigned），L 表示长整数（long） 后缀可以是大写，也可以是小写，U 和 L 的顺序任意。

85         // 十进制
0213       // 八进制 
0x4b       // 十六进制 
30         // 整数 
30u        // 无符号整数 
30l        // 长整数 
30ul       // 无符号长整数
*/

/*
浮点常量
3.14159       // 合法的 
314159E-5L    // 合法的 
510E          // 非法的：不完整的指数
210f          // 非法的：没有小数或指数
.e55          // 非法的：缺少整数或分数
*/

/*
布尔常量
true 值代表真。
false 值代表假。
*/

/*
字符常量

转义序列	含义
\\	\ 字符
\'	' 字符
\"	" 字符
\?	? 字符
\a	警报铃声
\b	退格键
\f	换页符
\n	换行符
\r	回车
\t	水平制表符
\v	垂直制表符
\ooo	一到三位的八进制数
\xhh . . .	一个或多个数字的十六进制数

*/


//字符串常量

// 定义常量
/*
使用 #define 预处理器。 #define identifier value
使用 const 关键字。 const type variable = value;
*/


using namespace std;

#define LENGTH 10
#define WIDTH 5
#define NEWLINE '\n'


int main(){
    cout << "hello\tword\n";
    cout << "NIHAO" << endl;

    const int LENGTH1 = 11;
    const int WIDTH1 = 6;
    const char NEWLINE1 = '\n';


    int area;
    int area1;

    area = LENGTH * WIDTH;
    cout << area;
    cout << NEWLINE;


    area1 = LENGTH1 * WIDTH1;
    cout << area1;
    cout << NEWLINE1;
    
    system("pause");
    
    return 0;
}