/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-26 07:23:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-26 07:41:39
 * @FilePath: /c++/knowledge/c++基础进阶/08-STL组件/07-有序关联容器.cpp
 * @Description: 注释信息
 */

#include <queue> // queue 和 priority_queue
#include <vector>
// 有序关联容器头文件
#include <set> // set 和 multiset  底层是红黑树
#include <map> // map 和 multimap  底层是红黑树
// 无序关联容器文件
#include <unordered_map> // unordered_set 和 unordered_multiset
#include <unordered_set> // unordered_map 和 unordered_multimap

#include <iostream>

class Student
{
private:
    int _id;
    std::string _name;

public:
    Student(int id = 0, std::string name = "") : _id(id), _name(name) {}
    friend std::ostream &operator<<(std::ostream &os, const Student &s); // 友元函数

    // 自定义< ,按学生ID排序
    bool operator<(const Student &rhs) const // 常方法
    {
        return _id < rhs._id;
    }

    ~Student() {}
};

std::ostream &operator<<(std::ostream &os, const Student &s)
{
    os << "[Student] id: " << s._id << " name: " << s._name << "\n";
    return os;
}

int main()
{
    // 有序关联容器-set
    std::cout << "\n===============set====================\n";
    std::set<int> s; // 单重集合， 不允许重复key
    for (int i = 0; i < 30; i++)
    {
        s.insert(i);
    }

    for (auto &&i : s)
    {
        std::cout << "s element: " << i << "\n"; // 从下到大有序输出
    }

    std::cout << "\n===================================\n";
    std::set<Student> s1;
    s1.insert(Student(1, "Alice"));
    s1.insert(Student(2, "Bob"));
    s1.insert(Student(3, "Charlie"));
    s1.insert(Student(4, "Dave"));

    for (auto &&i : s1)
    {
        std::cout << i << "\n";
    }

    // 有序映射表
    std::cout << "\n===============map====================\n";
    std::map<int, Student> m;
    m.insert(std::make_pair(1, Student(1, "Alice"))); // 插入
    m.insert(std::make_pair(2, Student(2, "Bob")));
    m.insert(std::make_pair(3, Student(3, "Charlie")));
    m.insert({4, Student(4, "Dave")});

    // 删除
    m.erase(1); // 删除key为1的元素

    // 查询
    std::cout << m[1] << "\n";    // 查询key为1的元素; operator[key] 如果key存在则修改，key不存在则创建默认值
    std::cout << m.at(2) << "\n"; // 查询key为2的元素
    auto it = m.find(2);          // 查询key为2的元素
    if (it != m.end())
    {
        std::cout << "find key: " << it->first << "\n";
        std::cout << "find value: " << it->second << "\n";
    }

    for (auto &&i : m)
    {
        std::cout << i.second << "\n";
    }
}