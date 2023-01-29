/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-18 06:37:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-01-29 23:54:59
 * @FilePath: /c++/practices/markdown_parser/main.cpp
 * @Description: 注释信息
 */
//
//  main.cpp
//  MarkdownParser
//

// #include <fostream>         // std::ofstream
// #include "mdtransform.hpp"  // ��Ҫʵ�ֵ� Markdown ������

#include "ParserCore.h"
#include <iostream>
#include <fstream>

int main()
{
    MarkdownParser markdown_parser("test.md");
    std::string table = markdown_parser.getTableOfContent();
    // std::cout <<  table << std::endl;
    std::string contents = markdown_parser.getContents();
    // std::cout <<  contents << std::endl;

    std::string head = "<!DOCTYPE html>\
                        <html lang=\"en\">\
                            <head>\
                                <meta charset=\"UTF-8\">\
                                <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
                                <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
                                <title>Document</title>\
                            </head><body>";
    std::string end = "</body></html>";
    std::ofstream out;
    out.open("测试markdown解析.html");
    out << head + table + contents + end;

    out.close();
    return 0;
}
