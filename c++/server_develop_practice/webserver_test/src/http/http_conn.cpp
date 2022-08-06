/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-06 13:37:48
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-06 16:45:30
 * @FilePath: /c++/server_develop_practice/webserver_test/src/http/http_conn.cpp
 * @Description: 注释信息
 */

#include "http_conn.h"

const char *ok_200_title = "OK";
const char *error_400_title = "Bad Request";
const char *error_400_form = "Your request has bad syntax \n";
const char *error_403_title = "Forbidden";
const char *error_403_form = "You do not have permission to get file from this server \n";
const char *error_404_title = "Not Found";
const char *error_404_form = "The requested file was not found \n";
const char *error_500_title = "Internal Error";
const char *error_500_form = "There was an unusual problem serving the request file \n";

locker m_lock;
std::map<std::string, std::string> users;

void http_conn::initmysql_result(mysql_conn_pool *connPool)
{
    // 先从连接池中取出一个连接
    MYSQL *mysql = NULL;
    connectionRAII mysqlcon(&mysql, connPool);

    // 从user表中检索 username，password数据
    if (mysql_query(mysql, "select username,passwd from user"))
    {
        LOG_ERROR("select error:%s\n", mysql_error(mysql));
    }

    // 从表中检索完整的结果集合
    MYSQL_RES *result = mysql_store_result(mysql);

    // 返回结果集中的列数
    int num_fields = mysql_num_fields(result);

    // 返回所有字段结构的数组
    MYSQL_FIELD *fields = mysql_fetch_field(result);

    // 从结果集中获取下一行， 将对应的用户名和密码存入map中
    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        std::string temp1(row[0]);
        std::string temp2(row[1]);
        users[temp1] = temp2;
    }
}

// 对文件描述符设置 非阻塞
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

// 将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
void addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)
    {
        event.events == EPOLLIN | EPOLLET | EPOLLRDHUP;
    }
    else
    {
        event.events == EPOLLIN | EPOLLRDHUP;
    }

    if (one_shot)
    {
        event.events |= EPOLLONESHOT;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

// 从内核时间表 删除描述符
void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

// 将事件重置为EPOLLLONESHOT
void modfd(int epollfd, int fd, int ev, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)
    {
        event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    }
    else
    {
        event.events = ev | EPOLLONESHOT | EPOLLRDHUP;
    }

    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

int http_conn::m_user_count = 0;
int http_conn::m_epollfd = -1;

// 关闭连接，关闭一个连接，客户端总量减1
void http_conn::close_conn(bool real_close)
{
    if (real_close && (m_sockfd != -1))
    {
        printf("close %d \n", m_sockfd);
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--;
    }
}

// 初始化连接，外部调用初始化套接字地址
void http_conn::init(int sockfd, const sockaddr_in &addr, char *root, int TRIGMode,
                     int close_log, std::string user, std::string passwd, std::string sqlname)
{
    m_sockfd = sockfd;
    m_address = addr;

    addfd(m_epollfd, sockfd, true, m_TRIGMode);
    m_user_count++;

    //当浏览器出现连接重置时
    doc_root = root;
    m_TRIGMode = TRIGMode;
    m_close_log = close_log;

    strcpy(sql_user, user.c_str());
    strcpy(sql_passwd, passwd.c_str());
    strcpy(sql_name, sqlname.c_str());

    init();
}

// 初始化新接受的连接
// check_state默认为分析 请求行状态
void http_conn::init()
{
    mysql = NULL;
    bytes_to_send = 0;
    bytes_have_send = 0;
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_linger = false;
    m_method = GET;
    m_url = 0;
    m_version = 0;
    m_content_length = 0;
    m_host = 0;
    m_start_line = 0;
    m_checked_idx = 0;
    m_read_idx = 0;
    m_write_idx = 0;
    cgi = 0;
    m_state = 0;
    timer_flag = 0;
    improv = 0;

    std::memset(m_read_buf, '\0', READ_BUFFER_SIZE);
    std::memset(m_write_buf, '\0', WRITE_BUFFER_SIZE);
    std::memset(m_real_file, '\0', FILENAME_LEN);
}

// 从状态机，用于分析出一行内容
// 从返回值为行的读取状态，有LINE_OK，LINE_BAD,LINE_OPEN
http_conn::LINE_STATUS http_conn::parse_line()
{
}

// 循环读取客户端数据， 直到无数据可读 或对方关闭连接
// 非阻塞ET工作模式下，需要一次性将数据读完
bool http_conn::read_once()
{
}

// 解析http的请求行， 获得请求方法，目标url及http版本号
http_conn::HTTP_CODE http_conn::parse_request_line(char *text)
{
}

// 解析http的头信息
http_conn::HTTP_CODE http_conn::parse_headers(char *text)
{
}

// 判断http请求是否被完整读入
http_conn::HTTP_CODE http_conn::parse_content(char *text)
{
}

http_conn::HTTP_CODE http_conn::process_read() {}

http_conn::HTTP_CODE http_conn::do_request() {}

void http_conn::unmap() {}

bool http_conn::write() {}

bool http_conn::add_response(const char *format, ...) {}

bool http_conn::add_status_line(int status, const char *title) {}

bool http_conn::add_headers(int content_len) {}

bool http_conn::add_content_length(int content_len) {}

bool http_conn::add_content_type() {}

bool http_conn::add_linger() {}

bool http_conn::add_blank_line() {}

bool http_conn::add_content(const char *content) {}

bool http_conn::process_write(HTTP_CODE code) {}

void http_conn::process() {}

http_conn::http_conn(/* args */)
{
}

http_conn::~http_conn()
{
}