#include "message.h"

#include <iostream>

int main()
{
    message say_hello("hello,GZY");
    std::cout << say_hello << std::endl;

    message say_byebye("byebye,GZY");
    std::cout << say_byebye << std::endl;

    return 0;
}