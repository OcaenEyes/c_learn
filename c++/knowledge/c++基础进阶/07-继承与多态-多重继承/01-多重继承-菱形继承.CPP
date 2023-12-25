
/**
 * c++的的多重继承 -- 菱形继承
 *
 */
class A
{
private:
protected:
    int ma;

public:
    A(int data = 0) : ma(data)
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

class B : public A
{
    protected:
    int mb;

public:
    B(int data = 0) : A(data),mb(data){
        std::cout << "B()" << std::endl;
    }
    ~B(){
        std::cout << "~B()" << std::endl;
    }

};

#include <iostream>

int main()
{
    return 0;
}