#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

/// @brief 创建socket
/// @param domain  指定底层协议族:对于TCP/IP协议族,PF_INET用于IPv4,PF_INET6用于IPv6; 对于UNIX本地域协议族,则为PF_UNIX
/// @param type     指定服务类型:SOCK_STREAM流服务、SOCK_UGRAM数据报服务； 对TCP/IP协议族，SOCK_STREAM表示传输层使用TCP协议、SOCK_UGRAM表示传输层使用UDP协议
/// @param protocol  在前两个参数协议集合下，选择具体的协议; 0表示默认协议
/// @return  调用成功则返回一个socket文件描述符,失败则返回-1并设置errno
int socket(int domain, int type, int protocol) {}

/// @brief 命名socket：将一个socket和socket地址绑定称为命名，服务器程序通常要命名socket，只有命名后客户端才知道如何连接它； 客户端则不需要命名socket
/// @param sockfd
/// @param my_addr  bind将my_addr所指向的socket地址,分配给未命名的sockfd文件描述符,
/// @param addr_len  指socket地址的长度
/// @return bind成功返回0, 失败返回-1并设置errno
///         常见errno包括：EACCESS -指被绑定的地址是受保护的地址，仅超级用户能访问;
///                      EADDRINUSE - 指被绑定的地址正在使用中，譬如将socket绑定到了处于TIME_WAIT状态的socket地址
int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addr_len) {}

/// @brief 监听socket，服务器通过listen调用来被动接受连接
/// @param sockfd 指被监听的socket
/// @param backlog  指提示内核监听队列的最大长度； 如果监听队列的长度超过backlog，服务器将不受理新的客户端连接， 客户端将收到ECONNREFUSED错误消息
/// @return 成功时返回0 ，失败返回-1
int listen(int sockfd, int backlog) {}

/// @brief 接受连接【从listen监听队列中接受一个连接】，只是从监听队列中取出连接，而不论连接处于何种状态
/// @param sockfd  是执行过listen系统调用的监听socket
/// @param addr  用来获取被接受连接的远端socket地址，该地址的长度由addrlen控制
/// @param addrlen
/// @return 成功时返回一个新的连接socket，该socket唯一的标识了被接受的这个连接；  服务器可以通过读写该socket来与被接受连接对应的客客户端通信； 失败返回-1并设置errno
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {}

/// @brief  客户端发起连接
/// @param sockfd 由socket系统调用返回一个socket
/// @param serv_addr 服务器监听的socket地址，addrlen表示该地址的长度
/// @param addrlen
/// @return 成功返回0，一旦成功建立连接，sockfd就唯一的标识了这个连接，客户端就可以通过读写sockfd与服务器通信； 失败返回-1并设置errno
int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen) {}

/// @brief 关闭连接，实际上就是关闭该连接对应的socket， 可通过关闭普通文件描述符的系统调用实现
/// @param fd 待关闭的socket； 非立即关闭，而是将fd的引用计数减1
/// @return
int close(int fd) {}

/// @brief 立即终止连接
/// @param sockfd 待关闭的socket
/// @param howto shutdown行为类型，SHUT_RD关闭读的一半,SHUT_WR关闭写的一半,SHUT_RDWR同时关闭读写
/// @return
int shutdown(int sockfd, int howto) {}

/* TCP 数据读写 */
/// @brief 读取sockfd上的数据
/// @param sockfd
/// @param buf 缓冲区位置
/// @param len 缓冲区大小
/// @param flags
/// @return 读取成功返回实际读取到的数据的长度。 它可能小于我们期望的长度len，因此祖耀多次调用recv才能读取完全数据； 可能返回0表示对方关闭连接； 出错返回-1并设置errno
ssize_t recv(int sockfd, void *buf, size_t len, int flags) {}

/// @brief 往sockfd上写入数据
/// @param sockfd
/// @param buf 缓冲区位置
/// @param len 缓冲区大小
/// @param flags
/// @return 写入成功返回实际写入的数据的长度。 出错返回-1并设置errno
ssize_t send(int sockfd, void *buf, size_t len, int flags) {}

/*UDP 数据读写*/

/// @brief UDP读取数据
/// @param sockfd
/// @param buf  缓冲位置
/// @param len 缓冲大小
/// @param flags
/// @param src_addr  每次读取数据都需要获取发送端的socket地址
/// @param addrlen
/// @return
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {}

/// @brief UDP发送数据
/// @param sockfd
/// @param buf 缓冲位置
/// @param len 缓冲大小
/// @param flags
/// @param dest_addr 每次发送数据都需要指定接收端的socket地址
/// @param addrlen
/// @return
ssize_t sendto(int sockfd, void *buf, size_t len, int flags, struct sockaddr *dest_addr, socklen_t *addrlen) {}

/* 通用数据读写函数 */

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {}
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags) {}

struct msghdr
{
    void *msg_name;           // socket 地址
    socklen_t msg_namelen;    // socket 地址的长度
    struct iovec *msg_iov;    // 分散的内存块
    int msg_iovlen;           // 分散的内存块数量
    void *msg_contolr;        // 指向辅助数据的起始位置
    socklen_t msg_controllen; // 辅助数据的大小
    int msg_flags;            // 复制函数中的flags参数，并在调用过程中更新
};

/**
 * @description: 带外标记
 * @param {int} sockfd 判断sockfd是否处于带外标记，即下一个被读到的数据是否是带外数据；如果是则返回1，此时可用MSG_OOB标识的recv来接收带外数据
 * @return {*}
 */
int sockatmark(int sockfd) {}

/* 地址信息函数 */
/**
 * @description: 获取sockfd 对应的本端socket地址， 并将其存储在address参数指定的内存中， 该socket地址的长度则存储与addrlen参数指向的变量中
 * @param {int} sockfd
 * @param {sockaddr*} address
 * @param {socklen_t*} addrlen
 * @return {*}
 */
int getsockname(int sockfd, struct sockaddr *address, socklen_t *addrlen) {}

/**
 * @description: 获取sockfd 对应的远端socket地址， 并将其存储在address参数指定的内存中， 该socket地址的长度则存储与addrlen参数指向的变量中
 * @param {int} sockfd
 * @param {sockaddr*} address
 * @param {socklen_t*} addrlen
 * @return {*}
 */
int getpeername(int sockfd, struct sockaddr *address, socklen_t *addrlen) {}