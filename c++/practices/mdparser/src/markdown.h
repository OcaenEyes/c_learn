/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-30 21:51:45
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-02-01 12:00:34
 * @FilePath: /c++/practices/mdparser/src/markdown.h
 * @Description: 注释信息
 */
#ifndef MARKDOWN_CORE_H
#define MARKDOWN_CORE_H

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

class markdown
{
private:
    /* data */
    enum MDType
    {
        INCODE,
        NORMAL,
        INBLOCK,
        INTABLE,
        TABLE_FMT
    } mdtype;

    std::string title;
    std::vector<std::string> content;
    std::vector<std::string> output;
    size_t content_length;

    struct Toc
    {
        int deep;
        std::string name;
    };
    std::string toc_content;
    int toc_number = 0;
    std::vector<struct Toc> tocs;
    std::vector<std::string> toc_string;
    bool needToc = 0;
    int isToc(std::string s);
    void generateToc();

    int isHead(std::string s);
    std::string generateHead(std::string s,int headLevel);

    int isHorizon(std::string s);
    std::string generateHorizon();

    int isList(std::string s);
    void generateList();

    int isUnList(std::string s);
    void generateUnList();

    int block_number = 0;
    int isBlockQuote(std::string s);
    std::string generateBlockQuote(std::string s, int number);
    int generateBlockQuote_S(std::string s);

    bool needMathJax = 0;

    bool isBr(std::string s);

    int isCode(std::string s);
    bool generateCode(std::string s);

    int table_number = 0;
    std::vector<std::string> aligns;
    bool generateTable(std::string s);
    std::vector<std::string> getTableElem(std::string s);

    void generateFlow();

    void tokenTool();

    std::string preReplace(std::string s);

public:
    markdown(/* args */);
    ~markdown();

    void outputMarkdown(std::vector<std::string> &_detail);
    void setTitle(std::string _title);

    int getContent(std::vector<std::string> &_content);

    int generatePre();
    int generateCore();
};
#endif