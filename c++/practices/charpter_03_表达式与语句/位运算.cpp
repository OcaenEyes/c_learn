#include <iostream>
using namespace std;

int main()
{
    long nWord = 0x12345678;
    int nBits;
    nBits = nWord & 0xFFFF;
    printf("low bits are 0x%x \n", nBits);
    nBits = (nWord & 0xFFFF0000) >> 16;
    printf("hight bits is 0x%x \n", nBits);
    return 0;
}