#include "pch.h"
#include <iostream>


int gdata1= 10;
int gdata2= 0;
int gdata3;

static int gdata4=11;
static int gdata5= 0;
static int gdata6;

int main(){

    int data1= 10;
    int data2= 0;
    int data3;

    static int data4=11;
    static int data5= 0;
    static int data6;

    std::cout << "gdata1: " << gdata1 << std::endl;
    std::cout << "gdata2: " << gdata2 << std::endl;
    std::cout << "gdata3: " << gdata3 << std::endl;
    std::cout << "gdata4: " << gdata4 << std::endl;
    std::cout << "gdata5: " << gdata5 << std::endl;
    std::cout << "gdata6: " << gdata6 << std::endl;

    std::cout << "data1: " << data1 << std::endl;
    std::cout << "data2: " << data2 << std::endl;
    std::cout << "data3: " << data3 << std::endl;
    std::cout << "data4: " << data4 << std::endl;
    std::cout << "data5: " << data5 << std::endl;
    std::cout << "data6: " << data6 << std::endl;

    return 0;
}