/*
    数据类型	  描述
    ofstream	该数据类型表示输出文件流，用于创建文件并向文件写入信息。
    ifstream	该数据类型表示输入文件流，用于从文件读取信息。
    fstream	    该数据类型通常表示文件流，且同时具有 ofstream 和 ifstream 两种功能，这意味着它可以创建文件，向文件写入信息，从文件读取信息。
*/

// 打开文件
// void open(const char *filename , ios::openmode mode);
/*
    在这里，open() 成员函数的第一参数指定要打开的文件的名称和位置，第二个参数定义文件被打开的模式。
    模式标志	描述
    ios::app	追加模式。所有写入都追加到文件末尾。
    ios::ate	文件打开后定位到文件末尾。
    ios::in	打开文件用于读取。
    ios::out	打开文件用于写入。
    ios::trunc	如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0。
*/

/*
以写入模式打开文件，并希望截断文件，以防文件已存在
ofstream outfile;
outfile.open("file.dat", ios::out | ios::trunc );
*/

/*
打开一个文件用于读写
ifstream  afile;
afile.open("file.dat", ios::out | ios::in );
*/

/*
关闭文件
void close();
*/

/*
流插入运算符（ << ）向文件写入信息
流提取运算符（ >> ）从文件读取信息
*/

#include <fstream>
#include <iostream>
using namespace std;

int main(){
    char data[100];

    // 以写模式打开文件
    ofstream outfile;
    outfile.open("afile.dat");

    cout << "write to the file" << endl;
    cout << "Enter ypur name" << endl;
    cin.getline(data,100);

    // 向文件写入 用户输入的数据
    outfile << data << endl;

    cout<< "enter your age: " <<endl;
    cin  >> data;
    cin.ignore();

    //再次向 文件写入用户输入的数据
    outfile << data << endl;

    //关闭打开的文件
    outfile.close();

    // 以读模式打开文件
    ifstream infile;
    infile.open("afile.dat");

    cout << "Reading from the file" << endl;
    infile >> data;

    // 在屏幕上写入数据
    cout << data <<endl;


    // 再次从文件读取数据，并显示它
    infile >> data; 
    cout << data << endl; 
 
    // 关闭打开的文件
    infile.close();

    return 0;
}


/* 文件位置指针

istream 和 ostream 都提供了用于重新定位文件位置指针的成员函数。这些成员函数包括关于 istream 的 seekg（"seek get"）和关于 ostream 的 seekp（"seek put"）
seekg 和 seekp 的参数通常是一个长整型
     第二个参数可以用于指定查找方向。
     查找方向可以是 ios::beg（默认的，从流的开头开始定位），
     也可以是 ios::cur（从流的当前位置开始定位），
     也可以是 ios::end（从流的末尾开始定位）。

文件位置指针是一个整数值，指定了从文件的起始位置到指针所在位置的字节数

定位 "get" 文件位置指针的实例：
// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
fileObject.seekg( n );
 
// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
fileObject.seekg( n, ios::cur );
 
// 把文件的读指针从 fileObject 末尾往回移 n 个字节
fileObject.seekg( n, ios::end );
 
// 定位到 fileObject 的末尾
fileObject.seekg( 0, ios::end );
*/