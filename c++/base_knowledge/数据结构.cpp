// C/C++ 数组允许定义可存储相同类型数据项的变量，
// 但是结构是 C++ 中另一种用户自定义的可用的数据类型，它允许您存储不同类型的数据项。

// 定义结构
// struct 数据结构 type_name
// {
//     /* data */
//     member_type1 member_name1;
//     member_type2 member_name2;
//     member_type3 member_name3;
//     member_type4 member_name4;
//     …
//     …
// } object_names;

#include <iostream>
#include <cstring>
using namespace std;

void printBook(struct Books book);
void printBookPointer(struct Books *book);

// 声明一个结构体类型
struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

typedef struct Books1
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
}Books1;

int main()
{
    Books Book1;
    Books Book2;

    // book1的描述
    strcpy(Book1.title, "C++ learn");
    strcpy(Book2.author, "gzy");
    strcpy(Book1.subject, "编程");
    Book1.book_id = 12345;

    // book2的描述
    strcpy(Book2.title, "C++");
    strcpy(Book2.author, "gzy");
    strcpy(Book2.subject, "技术");
    Book2.book_id = 12346;

    cout << "第一本书"
         << "\t" << Book1.title << "+" << Book1.author << "+" << Book1.subject << "+" << Book1.book_id << "\n";
    cout << "第二本书"
         << "\t" << Book2.title << "+" << Book2.author << "+" << Book2.subject << "+" << Book2.book_id << "\n";

    // 结构作为函数参数
    printBook(Book1);
    printBook(Book2);

    // 指向结构的指针
    printBookPointer(&Book1);
    printBookPointer(&Book2);

    return 0;
}

// 结构作为函数参数
void printBook(struct Books Book)
{
    cout << "结构作为函数参数"
         << "\n";
    cout << Book.title << "\t" << Book.author << "\t" << Book.subject << "\t" << Book.book_id << "\n";
}

// 指向结构的指针
void printBookPointer(struct Books *book)
{
    cout << "指向结构的指针"
         << "\n";
    cout << "第" << book << "本书"
         << "\t" << &book
         << "\t" << book->title << "\t" << book->author << "\t" << book->subject << "\t" << book->book_id << "\n";
}