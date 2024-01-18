
/**
 * 行为型模式：主要关注的是对象之间的通信
 * 观察者-监听者模式（发布-订阅模式）
 *      1.主要关注的是一对多的关系，也就是多个对象都依赖一个对象，当该对象的状态发生改变时，其他对象都能接收到相应的通知
 *
 * 譬如：一组数据（对象）====》通过该组数据===>生成曲线图； 当数据改变时曲线图应该及时收到相应的通知
 *
 *
 * observer1        observer2       observer3
 *          subject主题有变更时，应该及时通知观察者observer去处理相应的事件
 *
 */

#include <iostream>
#include <unordered_map>
#include <list>

// 观察者抽象类
class Observer
{
public:
    virtual void handle(int msgid) = 0;
};

class Observer1 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 1:
            std::cout << "observer1 recv msg 1\n";
            break;
        case 2:
            std::cout << "observer1 recv  msg 2\n";
            break;
        default:
            std::cout << "observer1 recv  unknown msg \n";
            break;
        }
    }
};

class Observer2 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {

        case 2:
            std::cout << "observer2 recv  msg 2\n";
            break;
        case 3:
            std::cout << "observer2 recv  msg 3\n";
            break;
        default:
            std::cout << "observer2 recv  unknown msg \n";
            break;
        }
    }
};

class Observer3 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {

        case 1:
            std::cout << "observer3 recv  msg 1\n";
            break;
        case 3:
            std::cout << "observer3 recv  msg 3\n";
            break;
        default:
            std::cout << "observer3 recv  unknown msg \n";
            break;
        }
    }
};

// 主题类
class Subject
{
public:
    void add_observer(Observer *obs, int msgid)
    {
        // sub_map[msgid].push_back(obs);
        auto it = sub_map.find(msgid);
        if (it != sub_map.end())
        {
            it->second.push_back(obs);
        }
        else
        {
            std::list<Observer *> lis;
            lis.push_back(obs);
            sub_map.insert({msgid, lis});
        }
    }

    // 主题检测发生改变时候， 通知相应的观察者对象处理事件
    void dispatch(int msgid)
    {
        auto it = sub_map.find(msgid);
        if (it != sub_map.end())
        {
            for (auto &&i : it->second)
            {
                i->handle(msgid);
            }
        }
    }

private:
    std::unordered_map<int, std::list<Observer *>> sub_map;
};

int main()
{
    Subject subject;

    Observer *p1 = new Observer1();
    Observer *p2 = new Observer2();
    Observer *p3 = new Observer3();

    subject.add_observer(p1, 1);
    subject.add_observer(p1, 2);
    subject.add_observer(p2, 2);
    subject.add_observer(p2, 3);
    subject.add_observer(p3, 1);
    subject.add_observer(p3, 3);

    int msgid = 0;

    while (true)
    {
        std::cout << "输入消息ID:\n";
        std::cin >> msgid;
        if (msgid == -1)
        {
            break;
        }
        subject.dispatch(msgid);
    }

    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
    delete p3;
    p3 = nullptr;
    return 0;
}