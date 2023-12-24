#include <iostream>

/**
 * c++运算符重载:使对象的运算表现 得和编译器内置
 *
 *
 */

class CComplex
{
public:
    CComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {}

    // // 加法运算符的重载；  指导编译器怎么做CComplex类对象的加法操作
    // CComplex operator+(const CComplex &c)
    // {
    //     // CComplex temp;
    //     // temp.mreal = mreal + c.mreal;
    //     // temp.mimage = mimage + c.mimage;
    //     // return temp;

    //     return CComplex(this->mreal + c.mreal, this->mimage + c.mimage);
    // }

    void show()
    {
        std::cout << "real:" << mreal << "  image:" << mimage << std::endl;
    }

private:
    int mreal;
    int mimage;

    // 友元函数
    friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);
};

CComplex operator+(const CComplex &lhs, const CComplex &rhs)
{
    return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}

int main()
{

    CComplex comp1(10, 10);
    CComplex comp2(20, 20);

    // comp1.operator+(comp2); 加法运算符的重载函数
    CComplex comp3 = comp1 + comp2;
    comp3.show();

    CComplex comp4 = comp1 + 20;
    comp4.show();

    // 编译器做对象运算时候，会调用对象的运算符重载函数(优先调用成员方法)； 如果没有成员方法，就在全局作用域找合适的运算符重载函数
    CComplex comp5 = 30 + comp1; 
    comp5.show();

    return 0;
}