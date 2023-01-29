/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-18 06:52:07
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-01-30 00:25:35
 * @FilePath: /c++/practices/markdown_parser/ParserCore.cpp
 * @Description: 注释信息
 */
#include "ParserCore.h"
#include <cstring>
#include <iostream>
#include <fstream>

MarkdownParser::MarkdownParser()
{
}

MarkdownParser::MarkdownParser(const std::string &filename)
{
    Croot = new CNode("");
    root = new Node(nul);
    now = root;
    std::ifstream fin(filename);

    bool newPara = false;
    bool inBlock = false;

    while (!fin.eof())
    {
        // 从文件中获取一行
        fin.getline(s, maxLength);

        // 处理不在代码块里 且需要换行的情况
        if (!inBlock && isCutline(s))
        {
            now = root;
            now->ch.push_back(new Node(hr));
            newPara = false;
            continue;
        }

        // std::pair 实质上是一个结构体， 可以将两个数据组合成一个数据
        // 计算一行中 开始的空格 和tab数
        std::pair<int, char *> ps = start(s);

        //  如果没有位置与代码块中，且没有统计到空格和Tab , 则直接读取下一行
        if (!inBlock && ps.second == nullptr)
        {
            now = root;
            newPara = true;
            continue;
        }

        // 分析该行文本的类型
        std::pair<int, char *> tj = judgeType(ps.second);

        // 如果是代码块类型
        if (tj.first == blockcode)
        {
            inBlock ? now->ch.push_back(new Node(nul)) : now->ch.push_back(new Node(blockcode));
            inBlock = !inBlock;
            continue;
        }

        // 如果在代码块中，直接讲内容拼接到当前节点中
        if (inBlock)
        {
            now->ch.back()->elem[0] += std::string(s) + '\n';
            continue;
        }

        // 如果是普通段落
        if (tj.first == paragraph)
        {
            if (now == root)
            {
                now = findNode(ps.first);
                now->ch.push_back(new Node(paragraph));
                now = now->ch.back();
            }

            bool flag = false;
            if (newPara && !now->ch.empty())
            {
                Node *ptr = nullptr;
                for (auto i : now->ch)
                {
                    if (i->type == nul)
                    {
                        ptr = i;
                    }
                }
                if (ptr != nullptr)
                {
                    makePara(ptr);
                }
                flag = true;
            }

            if (flag)
            {
                now->ch.push_back(new Node(paragraph));
                now = now->ch.back();
            }

            now->ch.push_back(new Node(nul));
            insert(now->ch.back(), std::string(tj.second));
            newPara = false;
            continue;
        }

        now = findNode(ps.first);

        // 如果是标题行，则向其标签中插入属性 tag
        if (tj.first >= h1 && tj.first <= h6)
        {
            now->ch.push_back(new Node(tj.first));
            now->ch.back()->elem[0] = "tag" + std::to_string(++cntTag);

            insert(now->ch.back(), std::string(tj.second));
            Cins(Croot, tj.first - h1 + 1, std::string(tj.second), cntTag);
        }

        // 如果是无序列表
        if (tj.first == ul)
        {
            if (now->ch.empty() || now->ch.back()->type != ul)
            {
                now->ch.push_back(new Node(ul));
            }
            now = now->ch.back();

            bool flag = false;
            if (newPara && !now->ch.empty())
            {
                Node *ptr = nullptr;
                for (auto i : now->ch)
                {
                    if (i->type == li)
                    {
                        ptr = i;
                    }
                }

                if (ptr != nullptr)
                {
                    makePara(ptr);
                }

                flag = true;
            }

            now->ch.push_back(new Node(li));
            now = now->ch.back();

            if (flag)
            {
                now->ch.push_back(new Node(paragraph));
                now = now->ch.back();
            }

            insert(now, std::string(tj.second));
        }

        // 如果是有序列表
        if (tj.first == ol)
        {
            if (now->ch.empty() || now->ch.back()->type != ol)
            {
                now->ch.push_back(new Node(ol));
            }
            now = now->ch.back();
            bool flag = false;

            if (newPara && !now->ch.empty())
            {
                Node *ptr = nullptr;
                for (auto i : now->ch)
                {
                    if (i->type == li)
                    {
                        ptr = i;
                    }
                }

                if (ptr != nullptr)
                {
                    makePara(ptr);
                }
                flag = true;
            }

            now->ch.push_back(new Node(li));
            now = now->ch.back();

            if (flag)
            {
                now->ch.push_back(new Node(paragraph));
                now = now->ch.back();
            }
            insert(now, std::string(tj.second));
        }

        // 如果是引用
        if (tj.first == quote)
        {
            if (now->ch.empty() || now->ch.back()->type != quote)
            {
                now->ch.push_back(new Node(quote));
            }
            now = now->ch.back();
            if (newPara || now->ch.empty())
            {
                now->ch.push_back(new Node(paragraph));
            }
            insert(now->ch.back(), std::string(tj.second));
        }
        newPara = false;
    }

    // 文件读取分析完毕
    fin.close();

    // 深入有限遍历整个语法树
    dfs(root);

    // 构造目录
    TOC += "<ul>";

    for (int i = 0; i < (int)Croot->ch.size(); i++)
    {
        /* code */
        Cdfs(Croot->ch[i], std::to_string(i + 1) + ".");
    }

    TOC += "</ul>";
}

MarkdownParser::~MarkdownParser()
{
    destroy<Node>(root);
    destroy<CNode>(Croot);
}

std::string MarkdownParser::getTableOfContent()
{
    return TOC;
}
// 获取markdown 内容
std::string MarkdownParser::getContents()
{
    return content;
}

// 判断是否是标题
inline bool MarkdownParser::isHeading(Node *v)
{
    return (v->type >= h1 && v->type <= h6);
}

// 判断是否是图片
inline bool MarkdownParser::isImage(Node *v)
{
    return v->type == image;
}

// 判断是否是超链接
inline bool MarkdownParser::isHref(Node *v)
{
    return v->type == href;
}

// 判断是否换行
bool MarkdownParser::isCutline(char *src)
{
    int cnt = 0;
    char *ptr = src;
    while (*ptr)
    {
        // 如果不是 空格、tab、- 或 *, 则不需要换行
        if (*ptr != ' ' && *ptr != '\t' && *ptr != '-')
        {
            return false;
        }
        if (*ptr == '-')
        {
            cnt++;
        }
        ptr++;
    }
    // 如果出现 --- 则需要增加一个分割线，这时需要换行
    return cnt >= 3;
}

// 生成段落
inline void MarkdownParser::makePara(Node *v)
{
    if (v->ch.size() == 1u && v->ch.back()->type == paragraph)
    {
        return;
    }
    if (v->type == paragraph)
    {
        return;
    }
    if (v->type == nul)
    {
        v->type = paragraph;
        return;
    }

    Node *x = new Node(paragraph);
    x->ch = v->ch;
    v->ch.clear();
    v->ch.push_back(x);
}

// 解析一行中的开始的空格和 Tab
// 返回值：由空格数 和有内容处的 char*指针 组成的std::pair
inline std::pair<int, char *> MarkdownParser::start(char *src)
{
    // 如果该行是空，则直接返回
    if ((int)strlen(src) == 0)
    {
        return std::make_pair(0, nullptr);
    }

    // 统计空格键 和Tab键的个数
    int cntSpace = 0, cntTab = 0;

    // 从该行的第一个字符串读， 统计空格键和tab键
    // 当遇到不是空格 和tab时 立即停止
    for (int i = 0; src[i] != '\0'; i++)
    {
        if (src[i] == ' ')
        {
            cntSpace++;
        }
        else if (src[i] == '\t')
        {
            cntTab++;
        }
        else
        {
            return std::make_pair(cntTab + cntSpace / 4, src + i);
        }
    }
    return std::make_pair(0, nullptr);
}

// 判断当前行的类型
// 返回值：当前行的类型 和除去行标志性关键字的 正式内容 char*指针 组成的std::pair
inline std::pair<int, char *> MarkdownParser::judgeType(char *src)
{
    char *ptr = src;

    // 跳过`#`
    while (*ptr == '#')
    {
        ptr++;
    }

    // 如果出现空格， 则说明是`<h>`标签
    if (ptr - src > 0 && *ptr == ' ')
    {
        return std::make_pair(ptr - src + h1 - 1, ptr + 1);
    }

    // 重置分析位置
    ptr = src;

    // 如果出现``` 则说明是 代码块
    if (std::strncmp(ptr, "```", 3) == 0)
    {
        return std::make_pair(blockcode, ptr + 3);
    }
    // 如果出现 * + -,并且下一个字符串是空格，则说明是列表
    if (std::strncmp(ptr, "- ", 2) == 0)
    {
        return std::make_pair(ul, ptr + 1);
    }

    // 如果出现 >,并且下一个字符串是空格，则说明是引用
    if (std::strncmp(ptr, "> ", 2) == 0)
    {
        return std::make_pair(quote, ptr + 1);
    }

    // 如果出现的是数字, 且下一个字符是 . 则说明是是有序列表
    char *ptr1 = ptr;
    while (*ptr1 && std::isdigit(*ptr1))
    {
        ptr1++;
    }
    if (ptr1 != ptr && *ptr1 == '.' && ptr1[1] == ' ')
    {
        return std::make_pair(ol, ptr1 + 1);
    }

    // 普通段落
    return std::make_pair(paragraph, ptr);
}

// 给定树深度寻找树的节点
inline Node *MarkdownParser::findNode(int depth)
{
    Node *ptr = root;
    while (!ptr->ch.empty() && depth != 0)
    {
        ptr = ptr->ch.back();
        if (ptr->type == li)
        {
            depth--;
        }
    }
    return ptr;
}

// 在节点中插入内容
void MarkdownParser::insert(Node *v, const std::string &src)
{
    int n = (int)src.size();
    bool incode = false,
         inem = false,
         instrong = false,
         inautolink = false;
    v->ch.push_back(new Node(nul));

    for (int i = 0; i < n; i++)
    {
        char ch = src[i];
        if (ch == '\\')
        {
            ch = src[++i];
            v->ch.back()->elem[0] += std::string(1, ch);
            continue;
        }

        // 处理行内代码
        if (ch == '`' && !inautolink)
        {
            incode ? v->ch.push_back(new Node(nul)) : v->ch.push_back(new Node(code));
            incode = !incode;
            continue;
        }

        // 处理加粗
        if (ch == '*' && (i < n - 1) && (src[i + 1] == '*') && !incode && !inautolink)
        {
            ++i;
            instrong ? v->ch.push_back(new Node(nul)) : v->ch.push_back(new Node(strong));
            instrong = !instrong;
            continue;
        }
        if (ch == '_' && !incode && !instrong && !inautolink)
        {
            inem ? v->ch.push_back(new Node(nul)) : v->ch.push_back(new Node(em));
            inem = !inem;
            continue;
        }

        // 处理图片
        if (ch == '!' && (i < n - 1) && (src[i + 1] == '[') && !incode && !instrong && !inem && !inautolink)
        {
            v->ch.push_back(new Node(image));
            for (i += 2; i < n - 1 && src[i] != ']'; i++)
            {
                v->ch.back()->elem[0] += std::string(1, src[i]);
            }
            i++;

            for (i++; i < n - 1 && src[i] != ' ' && src[i] != ')'; i++)
            {
                v->ch.back()->elem[1] += std::string(1, src[i]);
            }

            if (src[i] != ')')
            {
                for (i++; i < n - 1 && src[i] != ')'; i++)
                {
                    if (src[i] != '"')
                    {
                        v->ch.back()->elem[2] += std::string(1, src[i]);
                    }
                }
            }

            v->ch.push_back(new Node(nul));
            continue;
        }

        // 处理超链接
        if (ch == '[' && !incode && !instrong && !inem && !inautolink)
        {
            v->ch.push_back(new Node(href));
            for (i++; i < n - 1 && src[i] != ']'; i++)
            {
                v->ch.back()->elem[0] += std::string(1, src[i]);
            }
            i++;
            for (i++; i < n - 1 && src[i] != ' ' && src[i] != ')'; i++)
            {
                v->ch.back()->elem[1] += std::string(1, src[i]);
            }
            if (src[i] != ')')
            {
                for (i++; i < n - 1 && src[i] != ')'; i++)
                {
                    if (src[i] != '"')
                    {
                        v->ch.back()->elem[2] += std::string(1, src[i]);
                    }
                }
            }
            v->ch.push_back(new Node(nul));
            continue;
        }

        v->ch.back()->elem[0] += std::string(1, ch);
        if (inautolink)
        {
            v->ch.back()->elem[1] += std::string(1, ch);
        }
    }

    if (src.size() >= 2)
    {
        if (src.at(src.size() - 1) == ' ' && src.at(src.size() - 2) == ' ')
        {
            v->ch.push_back(new Node(br));
        }
    }
}

template <typename T>
void MarkdownParser::destroy(T *v)
{
    for (int i = 0; i < (int)v->ch.size(); i++)
    {
        destroy(v->ch[i]);
    }
    delete v;
}

void MarkdownParser::Cins(CNode *v, int x, const std::string &hd, int tag)
{
    int n = (int)v->ch.size();
    if (x == 1)
    {
        v->ch.push_back(new CNode(hd));
        v->ch.back()->tag = "tag" + std::to_string(tag);
        return;
    }

    if (!n || v->ch.back()->heading.empty())
    {
        v->ch.push_back(new CNode(""));
    }
    Cins(v->ch.back(), x - 1, hd, tag);
}

void MarkdownParser::Cdfs(CNode *v, std::string index)
{
    TOC += "<li>\n";
    TOC += "<a href=\"#" + v->tag + "\">" + index + " " + v->heading + "</a>\n";
    int n = (int)v->ch.size();

    if (n)
    {
        TOC += "<ul>\n";
        for (int i = 0; i <n; i++)
        {
            Cdfs(v->ch[i], index + std::to_string(i + 1) + ".");
        }
       
       TOC += "</ul>\n";
    }
    TOC += "</li>\n";
}

void MarkdownParser::dfs(Node *v)
{
    if (v->type == paragraph && v->elem[0].empty() && v->ch.empty())
    {
        return;
    }
    std::cout <<"********************************************************"  <<std::endl;
    std::cout <<"此时v->type是：" << v->type  <<std::endl;
    std::cout <<"此时startHtmlTag[v->type]是：" << startHtmlTag[v->type] <<std::endl;
    content += startHtmlTag[v->type];
    // std::cout <<"此时content是：" << content  <<std::endl;
    std::cout <<"********************************************************"  <<std::endl;
    bool flag = true;

    // 处理标题
    if (isHeading(v))
    {
        content += "id=\"" + v->elem[0] + "\">";
        flag = false;
    }

    // 处理超链接
    if (isHref(v))
    {
        content += "<a href=\"" + v->elem[1] + "\" title=\"" + v->elem[2] + "\">" + v->elem[0] + "</a>";
        flag = false;
    }

    // 处理图片
    if (isImage(v))
    {
        content += "<img alt=\"" + v->elem[0] + "\" src=\"" + v->elem[1] + "\" title=\"" + v->elem[2] + "\" />";
        flag = false;
    }

    // 如果上面三者都不是， 则直接添加内容
    if (flag)
    {
        content += v->elem[0];
        flag = false;
    }

    // 递归遍历所有
    for (int i = 0; i < (int)v->ch.size(); i++)
    {
        dfs(v->ch[i]);
    }

    // 拼接为结束标签
    content += endHtmlTag[v->type];
}