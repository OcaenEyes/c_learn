/*
序号	函数 & 描述
1	time_t time(time_t *time);      该函数返回系统的当前日历时间，自 1970 年 1 月 1 日以来经过的秒数。如果系统没有时间，则返回 -1。
2	char *ctime(const time_t *time);        该返回一个表示当地时间的字符串指针，字符串形式 day month year hours:minutes:seconds year\n\0。
3	struct tm *localtime(const time_t *time);       该函数返回一个指向表示本地时间的 tm 结构的指针。
4	clock_t clock(void);        该函数返回程序执行起（一般为程序的开头），处理器时钟所使用的时间。如果时间不可用，则返回 -1。
5	char * asctime ( const struct tm * time );      该函数返回一个指向字符串的指针，字符串包含了 time 所指向结构中存储的信息，返回形式为：day month date hours:minutes:seconds year\n\0。
6	struct tm *gmtime(const time_t *time);      该函数返回一个指向 time 的指针，time 为 tm 结构，用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示。
7	time_t mktime(struct tm *time);         该函数返回日历时间，相当于 time 所指向结构中存储的时间。
8	double difftime ( time_t time2, time_t time1 );         该函数返回 time1 和 time2 之间相差的秒数。
9	size_t strftime();      该函数可用于格式化日期和时间为指定的格式。
*/

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    // 基于当前系统的当前日期/时间
    time_t now = time(0);

    // 将now转换为字符串形式
    char *dt = ctime(&now);
    cout << "本地日期和时间" << dt << "\n";
    cout << "" << *dt << "\n";
    // 将now转换为 tm结构
    tm *gmtm = gmtime(&now);

    cout << "jie" << gmtm << "\n";

    dt = asctime(gmtm);
    cout << "utc 时间" << dt << "\n";

    return 0;
}
