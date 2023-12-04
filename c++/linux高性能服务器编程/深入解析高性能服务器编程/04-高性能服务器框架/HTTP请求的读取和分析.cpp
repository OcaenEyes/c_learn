#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096 // 读缓冲区大小

/*
 * 有限状态机的实例：HTTP请求的读取和分析
 */

// 主状态机有两种可能状态：分别表示当前正在分析请求行、当前正在分析头部字段
enum CHECK_STATE
{
    CHECK_STATE_REQUESTLINE = 0,
    CHECK_STATE_HEADER
};

// 从状态机的三种可能状态：即行的读取状态、分别表示：读取一个完整的行、行出错、行数据尚且不完整
enum LINE_STATUS
{
    LINE_OK = 0,
    LINE_BAD,
    LINE_OPEN
};

// 服务器处理HHTP请求的结果
enum HTTP_CODE
{
    NO_REQUEST = 0,    // 表示请求不完整，需要继续读取客户数据
    GET_REQUEST,       // 表示获得一个完整的客户请求
    BAD_REQUEST,       // 表示客户端请求有语法错误
    FORBIDEEN_REQUEST, // 表示客户端对资源没有足够的权限
    INTERNAL_ERROR,    // 表示服务器内部错误
    CLOSED_CONNECTION  // 表示客户端已关闭连接
};

// 简化返回，未给客户端完整的HTTP应答报文，只是根据服务器的处理结果发送“成功、失败”消息
static const char *szret[] = {"正常结果\n", "错误结果\n"};

// 从状态机，用于解析出一行内容
LINE_STATUS parse_line(char *buffer, int &checked_index, int &read_index)
{
    char temp;
    /**  checked_index 指向buffer(应用程序缓冲区)中，当前正在分析的字节，
     *   read_index指向buffer中客户数据的尾部的下一个字节
     *   buffer中第0～checked_index字节都已分析完毕，第chekced_index~(read_index-1)字节由下面的循环挨个分析
     */
    for (; checked_index < read_index; checked_index++)
    {
        // 获取当前要分析的字符
        temp = buffer[checked_index];
        // 如果当前字节是"\r"即回车符，则说明可能读取到一个完整的行
        if (temp == '\r')
        {
            // 如果"\r"字符碰巧是目前buffer中的最后一个已经被读入的客户数据，那么这次分析没有读到一个完整的行，则返回LINE_OPEN以表示还需要继续读取客户端数据才能进一步分析
            if ((checked_index + 1) == read_index)
            {
                return LINE_OPEN;
            }
            // 如果下一个字符是"\n"，则说明我们成功读取到一个完整行
            else if (buffer[checked_index + 1] == '\n')
            {
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }
            // 否则 说明客户发送的HTTP请求存在语法问题
            return LINE_BAD;
        }
        // 如果当前的字节是"\n",即换行符，则说明可能读取到一个完整的行
        else if (temp == '\n')
        {
            if ((checked_index > 1) && buffer[checked_index - 1] == '\r')
            {
                buffer[checked_index - 1] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    // 如果所有内容都分析完成也没有遇到"\r"字符、则返回LINE_OPEN，表示还需要继续读取客户数据才能进一步分析
    return LINE_OPEN;
}

// 分析请求行
HTTP_CODE parse_requestline(char *temp, CHECK_STATE &checkstate)
{
    /**
     *  char *strpbrk(const char *str1, const char *str2) 检索字符串 str1 中第一个匹配字符串str2 中字符的字符，不包含空结束字符
     *  依次检验字符串 str1 中的字符：
     *     - 当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置
     */
    char *url = strpbrk(temp, " \t");
    // 如果请求行中没有空白字符活“\t”，则HTTP请求必有问题
    if (!url)
    {
        return BAD_REQUEST;
    }
    *url++ = '\0';

    char *method = temp;
    /**
     * int strcasecmp (const char *s1, const char *s2);
     * C语言中判断字符串是否相等的函数，忽略大小写。s1和s2中的所有字母字符在比较之前都转换为小写。
     * 该strcasecmp()函数对空终止字符串进行操作。函数的字符串参数应包含一个(’\0’)标记字符串结尾的空字符。
     */
    if (strcasecmp(method, "GET") == 0) // 仅支持GET方法
    {
        printf("this request method id GET\n");
    }
    else
    {
        return BAD_REQUEST;
    }

    /**
     * C 库函数 size_t strspn(const char *str1, const char *str2)
     *  检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
     */
    url += strspn(url, " \t");
    char *version = strpbrk(version, " \t");

    // 仅支持HTPP/1.1
    if (strcasecmp(version, "HTTP/1.1") != 0)
    {
        return BAD_REQUEST;
    }

    // 检查URL是否合法
    /**
     * 函数 定义：int strncasecmp(const char *s1, const char *s2, size_t n)
     * 函数 说明：strncasecmp()用来比较参数s1和s2字符串前n个字符，比较时会自动忽略大小写的差异。
     * 返回值 ：若参数s1和s2字符串相同，则返回0； 若s1大于s2，则返回大于0的值； 若s1小于s2，则返回小于0的值
     */
    if (strncasecmp(url, "http://", 7) == 0)
    {
        url += 7;
        /**
         * strchr() 用于查找字符串中的一个字符，并返回该字符在字符串中第一次出现的位置。
         * strchr() 其原型定义在头文件 <string.h> 中,
         * char *strchr(const char *str, int c) 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
         * strchr() 函数返回的指针指向字符串中的字符，如果要将该指针用作字符串，应该将其传递给其他字符串处理函数，例如 printf() 或 strncpy()。
         */
        url = strchr(url, '/');
    }
    if (!url || url[0] != '/')
    {
        return BAD_REQUEST;
    }

    printf("the request URL is: %s\n", url);

    // HTTP请求行处理完毕，状态转移到头部字段的分析
    checkstate = CHECK_STATE_HEADER;
    return NO_REQUEST;
}

// 分析头部字段
HTTP_CODE parse_headers(char *temp)
{
    // 遇到一个空行，说明得到了一个正确的HTTP请求
    if (temp[0] == '\0')
    {
        return GET_REQUEST;
    }
    else if (strncasecmp(temp, "Host:", 5) == 0) // 处理HOST头文件
    {
        temp += 5;
        temp += strspn(temp, " \t");
        printf("the request host is: %s\n", temp);
    }
    else
    { // 其他头部字段都不处理
        printf("i can not handle this header\n");
    }
    return NO_REQUEST;
}

// 分析HTTP请求的入口函数
HTTP_CODE parse_content(char *buffer, int &checked_index, CHECK_STATE &checkstate, int &read_index, int &start_line)
{
    LINE_STATUS linestatus = LINE_OK; // 记录当前行的读取状态
    HTTP_CODE retcode = NO_REQUEST;   // 记录HTTP请求的处理结果
    // 主状态机，用于从buffer中取出所有完整的行
    while ((linestatus = parse_line(buffer, checked_index, read_index)) == LINE_OK)
    {
        char *temp = buffer + start_line; // start_line是在buffer中的起始位置
        start_line = checked_index;       // 记录下一行的起始位置
        // checkstate记录主状态机当前的状态
        switch (checkstate)
        {
        case CHECK_STATE_REQUESTLINE: // 第一个状态，分析请求行
            retcode = parse_requestline(temp, checkstate);
            if (retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            break;
        case CHECK_STATE_HEADER: // 第一个状态，分析头部字段
            retcode = parse_headers(temp);
            if (retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            else if (retcode == GET_REQUEST)
            {
                return GET_REQUEST;
            }
            break;
        default:
            return INTERNAL_ERROR;
        }
    }
    // 若没有读到一个完整的行，则表示还需继续读取客户数据才能进一步分析
    if (linestatus == LINE_OPEN)
    {
        return NO_REQUEST;
    }
    else
    {
        return BAD_REQUEST;
    }
}

int main(int argc, char *argv[])
{
}