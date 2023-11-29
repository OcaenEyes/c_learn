#include "sum_integers.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::vector<int> integers;
    std::cout << argc << std::endl;

    for (auto i = 1; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
        integers.push_back(std::stoi(argv[i]));
    }

    auto sum = sum_integers(integers);

    std::cout << sum << std::endl;

    return 0;
}