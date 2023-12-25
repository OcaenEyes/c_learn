#include <iostream>

/**
 * 1.继承的本质和原理
 * 2.派生类的构造过程
 * 3.重载、覆盖、异常
 * 4.静态绑定、动态绑定
 * 5.多态、vfptr和vftable
 * 6.抽象类的设计原理
 * 7.多重继承以及问题
 * 8.虚基类 vfptr和vftable
 * 9.RTTI
 * 10.c++四种类型强转
 */

/**
 * 继承的本质：
 *  a.代码的复用
 *  b.
 *
 * 类和类之间的关系：
 *  a.组合: a part of ...  一部分的关系
 *  b.继承: a kind of ...  一种的关系
 *
 *
 * 【基类成员的访问限定， 在派生类内是不能超过继承方式的】
 *  继承方式          基类的访问限定            派生类访问权限          外部访问权限
 *                     public                public                  true
 *   public            protected             protected               false
 *                     private               不可见                   false
 *
 *   protected         public                protected                false
 *                     protected             protected                false
 *                     private               不可见                    false
 *
 *   private           public                 private                 false
 *                     protected              private                 false
 *                     private                不可见                   false
 *
 * 默认继承方法
 *  1.class定义派生类： 默认继承方式private
 *  2.struct定义派生类：默认继承方式public
 *
 *
 */

class A
{
public:
    int ma;

protected:
    int mb;

private:
    int mc; // 只有自己 或 友元才能访问
};

class B : public A // 继承，A基类/父类 ，B派生类/子类
{                  // 会从A中继承来ma,mb,mc
public:
    int md;

    void func()
    {
        std::cout << "B::func()" << std::endl;
    }

protected:
    int me;

private:
    int mf;
};

int main()
{
}