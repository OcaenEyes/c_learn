/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-10 13:26:18
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-10 14:07:47
 * @FilePath: /c++/oceanim/v0.2/test/testjson/testjson.cpp
 * @Description: 注释信息
 */
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>

// json序列化示例1
void func1()
{
    nlohmann::json js;
    js["msg_type"] = 2;
    js["from"] = "gzy";
    js["to"] = "wsq";
    js["msg"] = "hell, nice to meet you!";
    std::cout << js << "\n";

    std::string sendBuf = js.dump();
    printf("%s\n", sendBuf.c_str());
}

// json序列化示例2
void func2()
{
    nlohmann::json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "gzy";

    // 添加对象
    js["msg"]["gzy"] = "hello,gzy";
    js["msg"]["wsq"] = "hello,wsq";
    //  添加对象,结果与上面的方式一致
    js["msg2"] = {{"wsq", "hello,wsq"}, {"gzy", "hello,gzy"}};

    std::cout << js << "\n";

    std::string sendBuf = js.dump();
    printf("%s\n", sendBuf.c_str());
}

// json序列化示例3
void func3()
{
    nlohmann::json js;

    // 直接序列话一个vector
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;

    // 直接序列化一个map容器
    std::map<int, std::string> m;
    m.insert({1, "G"});
    m.insert({2, "GZ"});
    m.insert({3, "GZY"});
    m.insert({4, "Zy"});
    js["name"] = m;
    std::cout << js << "\n";

    std::string sendBuf = js.dump(); // json数据对象 ---->序列化成字符串
    printf("%s\n", sendBuf.c_str());
}

// json的反序列化 json字符串----->反序列化成数据对象

std::string func4()
{
    nlohmann::json js;
    js["msg_type"] = 2;
    js["from"] = "gzy";
    js["to"] = "wsq";
    js["msg"] = "hell, nice to meet you!";
    std::cout << js << "\n";

    std::string sendBuf = js.dump();
    printf("%s\n", sendBuf.c_str());
    return sendBuf;
}

int main()
{
    std::cout << "===========1"
              << "\n";
    func1();
    std::cout << "===========2"
              << "\n";
    func2();

    std::cout << "===========3"
              << "\n";
    func3();

    std::cout << "===========4"
              << "\n"
              << "反序列化====="
              << "\n";
    std::string buf = func4();
    nlohmann::json json_res = nlohmann::json::parse(buf);
    std::cout << json_res["msg_type"] << "\n";
    return 0;
}