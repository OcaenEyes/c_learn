// 定义命名空间
/* 命名空间的定义使用关键字 namespace，后跟命名空间的名称，如下所示：

    namespace namespace_name {
     // 代码声明
    }
    为了调用带有命名空间的函数或变量，需要在前面加上命名空间的名称，如下所示：

    name::code;  // code 可以是变量或函数
*/
/*
    -using 指令
        - 使用 using namespace 指令，这样在使用命名空间时就可以不用在前面加上命名空间的名称
    - using 指令也可以用来指定命名空间中的特定项目
        - using std::cout;


*/

/*
    - 嵌套的命名空间
        - 命名空间可以嵌套，您可以在一个命名空间中定义另一个命名空间，如下所示：

        - namespace namespace_name1 {
        -    // 代码声明
        -    namespace namespace_name2 {
        -       // 代码声明
        -    }
        - }

        - 您可以通过使用 :: 运算符来访问嵌套的命名空间中的成员：

        - // 访问 namespace_name2 中的成员
        - using namespace namespace_name1::namespace_name2;
        - 
        - // 访问 namespace:name1 中的成员
        - using namespace namespace_name1;
*/
#include <iostream>
using namespace std;

// 第一个命名空间
namespace first_space
{
    void func()
    {
        cout << "Inside first_space" << endl;
    }
}
// 第二个命名空间
namespace second_space
{
    void func()
    {
        cout << "Inside second_space" << endl;
    }
}

int demo01()
{
    // 调用第一个命名空间中的函数
    first_space::func();
    // 调用第二个命名空间中的函数
    second_space::func();
    return 0;
}

int demo02()
{
    cout << "std::endl is used with std!" << std::endl;
    return 0;
}

int main()
{
    demo01();
    demo02();
    return 0;
}