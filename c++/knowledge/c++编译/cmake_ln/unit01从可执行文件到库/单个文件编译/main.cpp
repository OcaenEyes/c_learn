#include <cstdlib>
#include <iostream>
#include <string>

std::string say_hello()
{
    return std::string("helo,GZY!");
}

int main()
{
    std::cout << say_hello() << std::endl;
    return 0;
}
