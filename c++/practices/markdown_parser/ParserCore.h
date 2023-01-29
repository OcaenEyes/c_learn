/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-18 06:38:20
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-01-29 17:25:50
 * @FilePath: /c++/practices/markdown_parser/ParserCore.h
 * @Description: 注释信息
 */
#ifndef PARSERCORE_H
#define PARSERCORE_H

#include <string>
#include <vector>

#define maxLength 100000
// 词法枚举
enum
{
    nul = 0,
    paragraph = 1,
    href = 2,
    ul = 3,
    ol = 4,
    li = 5,
    em = 6,
    strong = 7,
    hr = 8,
    br = 9,
    image = 10,
    quote = 11,
    h1 = 12,
    h2 = 13,
    h3 = 14,
    h4 = 15,
    h5 = 16,
    h6 = 17,
    blockcode = 18,
    code = 19,
};

const std::string startHtmlTag[] = {
    "",
    "<p>",
    "",
    "<ul>",
    "<ol>",
    "<li>",
    "<em>",
    "<strong>",
    "<hr />",
    "<br />",
    "",
    "<blockquote>",
    "<h1 ",
    "<h2 ",
    "<h3 ",
    "<h4 ",
    "<h5 ",
    "<h6 ",
    "<pre><code>",
    "<code>"};

const std::string endHtmlTag[] = {
    "",
    "</p>",
    "",
    "</ul>",
    "</ol>",
    "</li>",
    "</em>",
    "</strong>"
    "",
    "",
    "",
    "</blockquote>",
    "</h1>",
    "</h2>",
    "</h3>",
    "</h4>",
    "</h5>",
    "</h6>",
    "</code></pre>",
    "</code>"};

typedef struct Node node;
struct Node
{
    int type;
    std::vector<node *> ch;
    std::string elem[3];

    Node(int _type) : type(_type) {}
};

typedef struct CNode cnode;
struct CNode
{
    std::vector<cnode *> ch;
    std::string heading;
    std::string tag;
    CNode(const std::string &hd) : heading(hd) {}
};

class MarkdownParser
{

private:
    std::string content;
    std::string TOC;
    Node *root;
    Node *now;
    CNode *Croot;
    int cntTag = 0;
    char s[maxLength];

    // 判断是否是标题
    bool isHeading(Node *v);

    // 判断是否是图片
    bool isImage(Node *v);

    // 判断是否是超链接
    bool isHref(Node *v);

    // 判断是否换行
    bool isCutline(char *src);

    // 生成段落
    void makePara(Node *v);

    // 解析一行中的开始的空格和 Tab
    std::pair<int, char *> start(char *src);

    // 判断当前行的类型
    std::pair<int, char *> judgeType(char *src);

    // 给定树深度寻找树的节点
    Node *findNode(int depth);

    // 在节点中插入内容
    void insert(Node *v, const std::string &src);

    template <typename T>
    void destroy(T *v);

    void Cins(CNode *v, int x, const std::string &hd, int tag);

    void Cdfs(CNode *v, std::string index);

    void dfs(Node *v);

public:
    MarkdownParser();

    MarkdownParser(const std::string &filename);

    // 获取markdown 目录
    std::string getTableOfContent();
    // 获取markdown 内容
    std::string getContents();

    ~MarkdownParser();
};

#endif