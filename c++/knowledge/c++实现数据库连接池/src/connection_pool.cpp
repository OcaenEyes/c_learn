/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 07:53:06
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-28 08:09:57
 * @FilePath: /c++/knowledge/c++实现数据库连接池/src/connection_pool.cpp
 * @Description: 注释信息
 */
#include "connection_pool.h"
#include "ini_config.hpp"
#include <thread>
#include <functional>
#include <chrono>

// 连接池的构造
ConnectionPool::ConnectionPool()
{
    if (!loadConfigFile())
    { // 加载失败
        return;
    }

    initPool();
}

ConnectionPool::~ConnectionPool()
{
}

bool ConnectionPool::loadConfigFile()
{
    INIConfig ini_config;
    bool _iniState = ini_config.readConfig("./conf/config.ini");
    if (!_iniState)
    {
        LOG_ERROR("读取配置文件失败");
        return false;
    }

    LOG_INFO("读取配置文件成功");

    _host = ini_config.readString("MySQL", "Host", "");
    _user = ini_config.readString("MySQL", "User", "");
    _password = ini_config.readString("MySQL", "Password", "");
    _database = ini_config.readString("MySQL", "Database", "");
    _port = ini_config.readInt("MySQL", "Port", 0);
    _initSize = ini_config.readInt("MySQL", "InitSize", 0);
    _maxConn = ini_config.readInt("MySQL", "MaxConn", 0);

    // _maxIdle = ini_config.readInt("MySQL", "MaxIdle", 0);
    _maxIdleTime = ini_config.readInt("MySQL", "MaxIdleTimeOut", 0);

    _connTimeout = ini_config.readInt("MySQL", "MaxConnectTimeOut", 0);
    // _rwTimeout = ini_config.readInt("MySQL", "MaxReadWriteTimeOut", 0);

    // _retryCount = ini_config.readInt("MySQL", "RetryCount", 0);
    // _retryInterval = ini_config.readInt("MySQL", "RetryInterval", 0);

    return true;
}

void ConnectionPool::initPool()
{
    // 创建初始数量的连接
    for (int i = 0; i < _initSize; i++)
    {
        MysqlConnection *p = new MysqlConnection();
        bool _state = p->connect(_host, _port, _database, _user, _password); // 创建连接
        if (_state)
        {
            _freeConnectionQues.push(p); // 连接入队
            p->refreshAliveTime();       // 刷新连接的存活时间
            // LOG_INFO("初始化，新的连接入队");
        }
    }

    // 启动一个新的线程 作为连接的生产者线程
    std::thread producer(std::bind(&ConnectionPool::produceConnectionTask, this));
    producer.detach(); // 分离线程，防止主线程退出，连接池线程也退出

    // 启动一个新的线程，扫描超过_maxIdleTime的连接，进行连接回收
    std::thread scanner(std::bind(&ConnectionPool::scanConnectionTask, this));
    scanner.detach(); // 分离线程，防止主线程退出，连接池线程也退出
}

// 运行在独立线程中， 专门负责生产新连接
void ConnectionPool::produceConnectionTask()
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock(_freeConnectionQuesMutex);
        while (!_freeConnectionQues.empty())
        {
            _cv.wait(lock); // 队列不为空，此处生产线程进入等待状态
        }

        if (_connCnt < _maxConn) // 当前连接数小于 最大阈值【连接数没有达到上限，则继续创建心连接】
        {
            MysqlConnection *p = new MysqlConnection();
            bool _state = p->connect(_host, _port, _database, _user, _password); // 创建连接
            if (_state)
            {
                _freeConnectionQues.push(p); // 连接入队
                p->refreshAliveTime();       // 刷新连接的活跃时间
                _connCnt++;                  // 连接数++
                LOG_INFO("连接不足，建新的连接入队");
            }
        }

        _cv.notify_all(); // 通知消费者线程，可以进行消费连接了
    }
}

// 运行在独立的线程中，专门负责销毁空闲连接
void ConnectionPool::scanConnectionTask()
{
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_maxIdleTime)); // 每_maxIdleTime检测一次
        // 扫描整个队列，释放多余连接
        std::unique_lock<std::mutex> lock(_freeConnectionQuesMutex);
        releaseConnection();
    }
}

// 线程安全的懒汉单例函数接口
ConnectionPool *ConnectionPool::getInstance()
{
    // 第一次运行的时候才会初始化
    static ConnectionPool connPool; // 静态变量， 由编译自动进行lock和unlock
    return &connPool;
}

// 给外部提供接口，从连接池中获取一个连接
std::shared_ptr<MysqlConnection> ConnectionPool::getConnection()
{
    // std::cout << "getConnection:" << _freeConnectionQues.size() << std::endl;
    std::unique_lock<std::mutex> lock(_freeConnectionQuesMutex);
    while (_freeConnectionQues.empty())
    {
        if (std::cv_status::timeout == _cv.wait_for(lock, std::chrono::milliseconds(_connTimeout)))
        {
            // 队列为空， 此处消费者线程进入等待状态,但设置超时时间, 超时醒来发现仍为空
            if (_freeConnectionQues.empty())
            {
                LOG_INFO("get connection timeout");
                return nullptr;
            }
        }
    }

    // std::shared_ptr智能指针析构时候，会把MysqlConnection资源直接delete掉， 相当于调用了MysqlConnection的析构函数，MysqlConnection就被close掉了
    // 此时需要自定义std::shared_ptr的释放资源方式，把MysqlConnection归还到_freeConnectionQues中
    // 采用lambda表达式的方法
    /**
     *   lambda表达式各个成员的解释
     *      captures 捕获列表，lambda可以把上下文变量以值或引用的方式捕获，在body中直接使用。
     *      tparams 模板参数列表(c++20引入)，让lambda可以像模板函数一样被调用。
     *      params 参数列表，有一点需要注意，在c++14之后允许使用auto左右参数类型。
     *      lambda-specifiers lambda说明符， 一些可选的参数，这里不多介绍了，有兴趣的读者可以去官方文档上看。这里比较常用的参数就是mutable和exception。其中，表达式(1)中没有trailing-return-type，是因为包含在这一项里面的。
     *      trailing-return-type 返回值类型，一般可以省略掉，由编译器来推导。
     *      body 函数体，函数的具体逻辑。
     *
     *
     *   捕获列表
     *      [] 什么也不捕获，无法lambda函数体使用任何
     *      [=] 按值的方式捕获所有变量
     *      [&] 按引用的方式捕获所有变量
     *      [=, &a] 除了变量a之外，按值的方式捕获所有局部变量，变量a使用引用的方式来捕获。这里可以按引用捕获多个，例如 [=, &a, &b,&c]。这里注意，如果前面加了=，后面加的具体的参数必须以引用的方式来捕获，否则会报错。
     *      [&, a] 除了变量a之外，按引用的方式捕获所有局部变量，变量a使用值的方式来捕获。这里后面的参数也可以多个，例如 [&, a, b, c]。这里注意，如果前面加了&，后面加的具体的参数必须以值的方式来捕获。
     *      [a, &b] 以值的方式捕获a，引用的方式捕获b，也可以捕获多个。
     *      [this] 在成员函数中，也可以直接捕获this指针，其实在成员函数中，[=]和[&]也会捕获this指针。
     *
     */
    std::shared_ptr<MysqlConnection> ptr(_freeConnectionQues.front(), [&](MysqlConnection *p)
                                         {
                                             // 此处是在服务器应用线程中调用，需要考虑线程安全
                                             std::unique_lock<std::mutex> lock(_freeConnectionQuesMutex);
                                             _freeConnectionQues.push(p); // 当智能指针析构的时候，还入队列中
                                             p->refreshAliveTime();       // 归还的时候重新刷新开始时间
                                         });

    _freeConnectionQues.pop(); // 连接出队

    if (_connCnt < _maxConn / 2) // 连接数少于最大连接数的一半， 则补充连接
    {
        _cv.notify_all(); // 通知等待的线程，可以继续生产连接了
    }

    return ptr;
}

void ConnectionPool::releaseConnection()
{
    while (_connCnt > _initSize)
    {
        MysqlConnection *p = _freeConnectionQues.front();
        if (p->getAliveTime() >= _maxIdleTime)
        {
            _freeConnectionQues.pop(); // 移出队列
            delete p;                  // 调用MysqlConnection的析构函数
            _connCnt--;                // 连接数量减减
            LOG_INFO("超时，连接出队");
        }
        else
        {
            break;
        }
    }
}
