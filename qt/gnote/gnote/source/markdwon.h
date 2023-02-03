#ifndef MARKDWON_H
#define MARKDWON_H


#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <stack>

class Markdown
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

public:
    Markdown(/* args */);
    ~Markdown();

    void outputMarkdown(std::vector<std::string> &_detail);
    void setTitle(std::string _title);

    int getContent(std::vector<std::string> &_content);

    int generatePre();
    int generateCore();
};

#endif // MARKDWON_H
