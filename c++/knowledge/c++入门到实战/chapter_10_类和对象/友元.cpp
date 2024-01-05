/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-14 10:52:44
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-14 21:29:29
 * @FilePath: /c++/knowledge/入门到实战/chapter_10_类和对象/友元.cpp
 * @Description: 注释信息
 */

/**
 * @brief
 * 使用friend关键， 让特定的函数或者别的类的所有函数 对私有数据成员进行读写
 * 可以再当前类中 将另一个类作为自己的友元类，这样再另一个类里就可以访问当前类的 私有成员了
 * @return int
 */

class testitem
{
private:
    /* data */
public:
    testitem(/* args */);
    ~testitem();
    friend class testclass; // testclass 作为自己的友元类
    friend void testfunc::optfunc(); // testfunc::optfunc 声明友元函数
};

testitem::testitem(/* args */)
{
}

testitem::~testitem()
{
}

class testclass
{
private:
    /* data */
    testitem _t;

public:
    testclass(/* args */);
    ~testclass();
};

testclass::testclass(/* args */)
{
}

testclass::~testclass()
{
}

class testfunc
{
private:
    /* data */
public:
    testfunc(/* args */);
    ~testfunc();
    void optfunc();
};

testfunc::testfunc(/* args */)
{
}

testfunc::~testfunc()
{
}


int main()
{
}