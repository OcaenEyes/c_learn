/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 23:26:15
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-09 23:39:35
 * @FilePath: /c++/practices/encryption_demo/src/test.cpp
 * @Description: 注释信息
 */
#include <iostream>
#include "cryptopp/integer.h"

using namespace CryptoPP;
int main(int argc, char *argv[])
{
    CryptoPP::Integer i;
    std::cout << "i:" << i << std::endl;
    std::cout << "hello~" << std::endl;

    return 0;
}