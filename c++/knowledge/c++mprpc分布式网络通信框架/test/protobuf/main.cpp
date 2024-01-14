#include "test.pb.h"

#include <iostream>

int main1()
{
    // 封装了login请求对象的数据
    fixbug::LoginRequest req;
    req.set_name("gzy");
    req.set_pwd("123456");

    // login请求对象的序列化到send_str
    std::string send_str;
    if (req.SerializeToString(&send_str)) // 序列化到send_str中
    {
        std::cout << "序列化成功： " << send_str.c_str() << "\n";
    }

    // 从send_str中 反序列化一个请求对象
    fixbug::LoginRequest reqq;
    if (reqq.ParseFromString(send_str))
    {
        std::cout << "反序列化成功： " << reqq.name() << "\n";
        std::cout << "反序列化成功： " << reqq.pwd() << "\n";
    }
    return 0;
}

int main()
{
    fixbug::LoginResponse rsp;
    fixbug::Response *res = rsp.mutable_res();
    res->set_errcode(1);
    res->set_errmsg("登录失败！");

    fixbug::GetFriendListRes frsp;
    fixbug::Response *rc = frsp.mutable_res();
    rc->set_errcode(0);

    fixbug::User *user = frsp.add_friendlist();
    user->set_name("gzy");
    user->set_age(20);

    fixbug::User *user2 = frsp.add_friendlist();
    user2->set_name("gzqay");
    user2->set_age(18);

    std::cout << frsp.friendlist_size() << "\n";

    return 0;
}