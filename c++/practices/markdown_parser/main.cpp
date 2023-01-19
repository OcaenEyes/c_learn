/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-18 06:37:12
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-01-18 06:37:13
 * @FilePath: /c++/practices/markdown_parser/main.cpp
 * @Description: 注释信息
 */
//
//  main.cpp
//  MarkdownParser
//

// #include <fostream>         // std::ofstream
// #include "mdtransform.hpp"  // ��Ҫʵ�ֵ� Markdown ������

// int main() {
//     // װ�ع��� Markdown �ļ�
//     MarkdownTransform transformer("test.md");

//     // ��дһ�� `getTableOfContents()` ��������ȡ Markdown �ļ� HTML ��ʽ��Ŀ¼
//     std::string table = transformer.getTableOfContents();

//     // ��дһ�� `getContents()` ��������ȡ Markdown ת�� HTML �������
//     std::string contents = transformer.getContents();

//     // ׼��Ҫд��� HTML �ļ�ͷβ��Ϣ
//     std::string head = "<!DOCTYPE html><html><head>\
//         <meta charset=\"utf-8\">\
//         <title>Markdown</title>\
//         <link rel=\"stylesheet\" href=\"github-markdown.css\">\
//         </head><body><article class=\"markdown-body\">";
//     std::string end = "</article></body></html>";

//     // �����д�뵽�ļ�
//     std::ofstream out;
//     out.open("output/index.html");
//     // ��ת��������ݹ��쵽 HTML �� <article></article> ��ǩ�ڲ�
//     out << head+table+contents+end;
//     out.close();
//     return 0;
// }
