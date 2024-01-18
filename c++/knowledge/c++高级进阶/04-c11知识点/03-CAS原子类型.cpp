

#include <atomic>

std::atomic_int cnt_;
std::atomic_bool isready;

int main()
{

    cnt_ = 0;
    isready = false;

    return 0;
}