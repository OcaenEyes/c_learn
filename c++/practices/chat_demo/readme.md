<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-08 23:40:23
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 00:43:14
 * @FilePath: /c++/practices/chat_demo/readme.md
 * @Description: 注释信息
-->

### 需求分析

在这个聊天室软件中我们有下面两个程序：

服务器：能够接受新的客户端连接，并将每个客户端发过来的消息发给所有其他的客户端
客户端：能够连接服务器，并向服务器发送消息，同时接收服务器发过来的任何消息
这个需求是最简单的聊天室需求，我们目前只实现了群聊，未来大家可以扩展到单独的两个客户端之间的私聊。为了降低学习的难度，突出重点，我们尽量将代码修改的简单，项目中复杂功能都去掉了，线程池、多线程编程、超时重传、确认收包等等都不会涉及。让大家真正了解C/S模型，以及epoll的使用。


### 抽象与细化

需求中的角色非常简单，同时功能也很简单，所以我们只需要根据功能角色设计客户端类和服务端类。

其中客户端类我们需要支持下面几个功能：
1. 连接服务器
2. 支持用户输入聊天消息，发送消息给服务器
3. 接收并显示服务器的消息
4. 退出连接

针对上述需求，客户端的实现需要两个进程分别支持下面的功能：

子进程的功能：
1. 等待用户输入聊天信息
2. 将聊天信息写到管道（pipe），并发送给父进程

父进程的功能：
1. 使用epoll机制接受服务端发来的信息，并显示给用户，使用户看到其他用户的聊天信息
2. 将子进程发给的聊天信息从管道（pipe）中读取, 并发送给服务端

服务端类需要支持：
1. 支持多个客户端接入，实现聊天室基本功能
2. 启动服务建立监听端口等待客户端连接
3. 使用epoll机制实现并发，增加效率
4. 客户端连接时发送欢迎消息并存储连接记录
5. 客户端发送消息时广播给其他所有客户端
6. 客户端请求退出时对连接信息进行清理

如果实现这两个类，我们需要先学习一些网络编程的基础知识。

### C/S模型

首先介绍下模型。服务端和客户端采用经典的C/S模型，并且使用TCP连接，模型如下：

image.png
解释如下：

服务器端：
1. socket()创建监听Socket
2. bind()绑定服务器端口
3. listen()监听客户端连接
4. accept()接受连接
5. recv/send接收及发送数据
6. close()关闭socket

客户端：
1. socket()创建监听Socket
2. connect()连接服务器
3. recv/send接收及发送数据
4. close()关闭socket

#### TCP服务端通信的常规步骤

1. 使用socket()创建TCP套接字（socket）
2. 将创建的套接字绑定到一个本地地址和端口上（Bind）
3. 将套接字设为监听模式，准备接收客户端请求（listen）
4. 等待客户请求到来: 当请求到来后，接受连接请求，返回一个对应于此次连接的新的套接字（accept）
5. 用accept返回的套接字和客户端进行通信（使用write()/send()或send()/recv() )
6. 返回，等待另一个客户请求
7. 关闭套接字

服务端流程示例代码：
```
//Server.cpp代码（通信模块）：
//服务端地址 ip地址 + 端口号
struct sockaddr_in serverAddr;
serverAddr.sin_family = PF_INET;
serverAddr.sin_port = htons(SERVER_PORT);
serverAddr.sin_addr.s_addr = inet_addr(SERVER_HOST);

//服务端创建监听socket
int listener = socket(PF_INET, SOCK_STREAM, 0);
if(listener < 0) { perror("listener"); exit(-1);}
printf("listen socket created \n");

//将服务端地址与监听socket绑定
if( bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind error");
    exit(-1);
}
//开始监听
int ret = listen(listener, 5);
if(ret < 0) { perror("listen error"); exit(-1);}
printf("Start to listen: %s\n", SERVER_HOST);
```

后续的accept连接以及具体通信，在解释了epoll之后才会介绍。

#### TCP客户端通信的常规步骤

1. 创建套接字（socket）
2. 使用connect()建立到达服务器的连接（connect)
3. 客户端进行通信（使用write()/send()或send()/recv())
4. 使用close()关闭客户连接

客户端流程示例代码：
```
//Client.cpp代码（通信模块）：
//客户要连接的服务端地址（ ip地址 + 端口号）
struct sockaddr_in serverAddr;
serverAddr.sin_family = PF_INET;
serverAddr.sin_port = htons(SERVER_PORT);
serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

// 创建套接字（socket）
int sock = socket(PF_INET, SOCK_STREAM, 0);
if(sock < 0) { perror("sock error"); exit(-1); }
//向服务器发出连接请求（connect）
if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("connect error");
    exit(-1);
}
```

客户端如何实现管道之间的通信，以及与服务端之间的通信，在后面会详细介绍。

完成这步后, 我们需要学习下几个比较重要的概念。

#### 阻塞与非阻塞socket
通常的，对一个文件描述符指定的文件或设备, 有两种工作方式: 阻塞与非阻塞方式。

1. 阻塞方式是指： 当试图对该文件描述符进行读写时，如果当时没有数据可读，或者暂时不可写，程序就进入等待状态，直到有东西可读或者可写为止。
2. 非阻塞方式是指： 如果没有数据可读，或者不可写，读写函数马上返回，而不会等待。

举个例子来说，比如说小明去找一个女神聊天，女神却不在。如果小明舍不得走，只能在女神大门口死等着，当然小明可以休息。当女神来了，她会把你唤醒（囧，因为挡着她门了），这就是阻塞方式。如果小明发现女神不在，立即离开，以后每隔十分钟回来看一下（采用轮询方式），不在的话仍然立即离开，这就是非阻塞方式，在他离开的十分钟内可以干别的事情。

阻塞方式和非阻塞方式唯一的区别： 是否立即返回。本项目采用更高效的做法，所以应该将socket设置为非阻塞方式。这样能充分利用服务器资源，效率得到了很大提高。

非阻塞设置方式示例代码：

```//将文件描述符设置为非阻塞方式（利用fcntl函数）
fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)| O_NONBLOCK);
```

#### epoll
前面介绍了阻塞和非阻塞方式，现在该介绍下epoll机制了。epoll真的是一个特别重要的概念，互联网公司面试后台开发，或者系统开发等相关职位都会问epoll机制。当服务端的在线人数越来越多，会导致系统资源吃紧，I/O效率越来越慢，这时候就应该考虑epoll了。epoll是Linux内核为处理大批句柄而作改进的poll，是Linux特有的I/O函数。其特点如下：

1. epoll是Linux下多路复用IO接口select/poll的增强版本。其实现和使用方式与select/poll有很多不同，epoll通过一组函数来完成有关任务，而不是一个函数。
2. epoll之所以高效，是因为epoll将用户关心的文件描述符放到内核里的一个事件表中，而不是像select/poll每次调用都需要重复传入文件描述符集或事件集。比如当一个事件发生（比如说读事件），epoll无须遍历整个被侦听的描述符集，只要遍历那些被内核IO事件异步唤醒而加入就绪队列的描述符集合就行了。
3. epoll有两种工作方式，LT(level triggered)：水平触发和ET(edge-triggered)：边沿触发。LT是select/poll使用的触发方式，比较低效；而ET是epoll的高速工作方式（本项目使用epoll的ET方式）。

通俗理解就是，比如说有一堆女孩，有的很漂亮，有的很凤姐。现在你想找漂亮的女孩聊天，LT就是你需要把这一堆女孩全都看一遍，才可以找到其中的漂亮的（就绪事件）；而ET是你的小弟（内核）将N个漂亮的女孩编号告诉你，你直接去看就好，所以epoll很高效。另外，还记得小明找女神聊天的例子吗？采用非阻塞方式，小明还需要每隔十分钟回来看一下（select）；如果小明有小弟（内核）帮他守在大门口，女神回来了，小弟会主动打电话，告诉小明女神回来了，快来处理吧！这就是epoll。

epoll 共3个函数, 如下:

创建一个epoll句柄：
```
// 创建一个epoll句柄，参数size用来告诉内核监听的数目，size为epoll所支持的最大句柄数，我们这里暂时忽略内核升级的问题。
int epoll_create(int size)
```
epoll事件注册函数：
```
/*
函数功能： epoll事件注册函数
　 参数epfd为epoll的句柄，即epoll_create返回值
　 参数op表示动作，用3个宏来表示：
　　  EPOLL_CTL_ADD(注册新的fd到epfd)， 
　EPOLL_CTL_MOD(修改已经注册的fd的监听事件)，
　　  EPOLL_CTL_DEL(从epfd删除一个fd)；
　　  其中参数fd为需要监听的标示符；
　 参数event告诉内核需要监听的事件，event的结构如下：
struct epoll_event {
  __uint32_t events; //Epoll events
  epoll_data_t data; //User data variable
};
其中介绍events是宏的集合，本项目主要使用EPOLLIN(表示对应的文件描述符可以读，即读事件发生)，其他宏类型，可以google之！
*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
```
等待事件的产生：
```
// 等待事件的产生，函数返回需要处理的事件数目（该数目是就绪事件的数目，就是前面所说漂亮女孩的个数N）
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
```
因此服务端使用epoll的时候，步骤如下：

1. 调用epoll_create函数在Linux内核中创建一个事件表；
2. 然后将文件描述符（监听套接字listener）添加到所创建的事件表中；
3. 在主循环中，调用epoll_wait等待返回就绪的文件描述符集合；
4. 分别处理就绪的事件集合，本项目中一共有两类事件：新用户连接事件和用户发来消息事件（epoll还有很多其他事件，本项目为简洁明了，不介绍）。

下面介绍如何将一个socket添加到事件表中，如下：
```
//将文件描述符fd添加到epollfd标示的内核事件表中， 并注册EPOLLIN和EPOOLET事件，EPOLLIN是数据可读事件；EPOOLET表明是ET工作方式。最后将文件描述符设置非阻塞方式
/**
  * @param epollfd: epoll句柄
  * @param fd: 文件描述符
  * @param enable_et : enable_et = true, 
     采用epoll的ET工 作方式；否则采用LT工作方式
**/
void addfd( int epollfd, int fd, bool enable_et )
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    setnonblocking(fd);
    printf("fd added to epoll!\n\n");
}
```

http://labfile.oss.aliyuncs.com/courses/1051/chatroom.zip