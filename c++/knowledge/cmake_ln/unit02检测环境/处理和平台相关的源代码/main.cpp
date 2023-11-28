#include <cstdlib>
#include <iostream>
#include <string>

std::string say_hello()
{
#ifdef IS_WINDOWS
    return std::string("hello,windows");
#elif IS_LINUX
    return std::string("hello,linux");
#elif IS_MACOS
    return std::string("hello,macOS");
#else
    return std::string("hello,unknown system");
#endif
}

int main()
{
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}