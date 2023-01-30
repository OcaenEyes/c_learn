/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-30 07:19:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-01-30 23:44:50
 * @FilePath: /c++/practices/mdparser/src/markdown.cpp
 * @Description: 注释信息
 */
#include "markdown.h"

void markdown::setTitle(std::string _title)
{
    title = _title;
}

int markdown::getContent(std::vector<std::string> &_content)
{
    content = _content;
    content_length = _content.size();
    return 0;
}

void markdown::outputMarkdown(std::vector<std::string> &_detail)
{
}

int markdown::generatePre()
{
    tokenTool();
    generateList();
    generateUnList();
    generateFlow();
    for (auto s : content)
    {
        if (needToc == 0)
            isToc(s);
        auto headLevel = isHead(s);

        if (generateBlock_S(s))
        {
        }
        else if (generateCode(s))
        {
        }
        else if (generateTable(s))
        {
        }
        else if (headLevel != 0)
        {
            output.push_back(generateHead(s, headLevel));
        }
        else if (isHorizon(s))
        {
            output.push_back(generateHorizon());
        }
        else if (isBr(s))
        {
            output.push_back("<br />");
        }
        else
        {
            output.push_back(s);
        }
    }
    return 0;
}

int markdown::generateCore(std::vector<std::string> &_content)
{
    content.clear();
    output.clear();
    aligns.clear();
    for (int i = 0; i < 10; i++)
    {
        aligns.push_back("center");
    }

    mdtype = NORMAL;

    block_number = 0;
    table_number = 0;

    output.push_back("<!DOCTYPE html>\
                        <html lang=\"en\">\
                        <head>\
                            <meta charset=\"UTF-8\">\
                            <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
                            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
                            <meta name=\"application author\" content=\"OCEAN GZY\">\
                            <title>Document</title>\
                        </head>\
                        <body>\
                            <div id=\"main\">");

    if (needToc)
    {
        generateToc();
    }
    output.push_back("<br />");
    generatePre();

    if (needMathJax)
    {
        std::vector<std::string>::iterator it = output.begin() + 4;
        output.erase(it);
    }

    output.push_back("</div>\
                    </body>\
                    </html>");
    return 0;
}

int markdown::isHead(std::string s)
{
    auto headLevel = 0;
    if (s.empty())
    {
        return 0;
    }

    while (s[headLevel] == '#')
    {
        ++headLevel;
        if (headLevel > 7)
            break;
    }

    if (headLevel > 7 && s[headLevel] != ' ')
    {
        headLevel = 0;
    }

    return headLevel;
}

std::string markdown::generateHead(std::string s, int headLevel)
{
    auto name = s.substr(headLevel + 1);
    auto tem = "<a name =\"" + name + "\"></a>";
    tem += "<h" + std::to_string(headLevel) + ">" + name + "</h" + std::to_string(headLevel) + ">";
    tocs.push_back(Toc{headLevel, name});
    return tem;
}

int markdown::isHorizon(std::string s)
{
    std::regex re_horizon("^[-*]{3,}$");
    std::smatch sm;
    std::regex_match(s, sm, re_horizon);
    if (sm.size() != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

std::string markdown::generateHorizon()
{
    return "<hr />";
}

int markdown::isUnList(std::string s)
{
    if (s.empty())
    {
        return 0;
    }

    auto idx = 0;
    while (s[idx] == ' ')
    {
        ++idx;
    }

    if (s[idx] == '+' || s[idx] == '-' || s[idx] == '*')
    {
        ++idx;
        if (idx < s.size() && s[idx] == ' ')
        {
            return idx;
        }
    }
    return 0;
}
void markdown::generateUnList()
{
    auto ii = 0;
    auto top = 0;
    std::stack<int> _stack;
    _stack.push(0);
    std::string _temp;
    for (auto i = 0; i < content.size(); ++i)
    {
        top = _stack.top();
        std::string s = content[i];
        ii = isUnList(s);

        if (ii <= 0)
        {
            _temp = "";
            while (ii < top)
            {
                _temp += "</ul>";
                _stack.pop();
                top = _stack.top();
            }
            _temp += s;
            content[i] = _temp;
            continue;
        }

        if (ii > _stack.top())
        {
            _temp = "<ul><li>" + s.substr(ii + 1) + "</li>";
            _stack.push(ii);
        }
        else if (ii == _stack.top())
        {
            _temp += "<li>" + s.substr(ii + 1) + "</li>";
        }
        else
        {
            _temp = "";
            while (ii < top)
            {
                _temp += "</ul>";
                _stack.pop();
                top = _stack.top();
            }

            if (ii > _stack.top())
            {
                _temp += "<ul><li>" + s.substr(ii + 1) = "</li>";
                _stack.push(ii);
            }
            else if (ii == _stack.top())
            {
                _temp += "<li>" + s.substr(ii + 1) + "</li>";
            }
        }
        content[i] = _temp;
    }
}

int markdown::isList(std::string s)
{
    std::regex re_list("^\\s*\\d+\\.\\s.+");
    std::smatch sm;
    std::regex_match(s, sm, re_list);
    if (sm.size() != 0)
    {
        auto idx = 0;
        while (s[idx] == ' ')
        {
            ++idx;
        }
        while (isdigit(s[idx])) // 判断字符或字符串是否是数字
        {
            ++idx;
        }
        return ++idx;
    }
    else
    {
        return 0;
    }
}
void markdown::generateList()
{
    auto ii = 0;
    auto top = 0;

    std::stack<int> _stack;
    _stack.push(0);
    std::string _temp;
    for (auto i = 0; i < content.size(); ++i)
    {
        top = _stack.top();
        std::string s = content[i];
        ii = isList(s);
        if (ii <= 1)
        {
            _temp = "";
            while (ii < top)
            {
                _temp += "</ol>";
                _stack.pop();
                top = _stack.top();
            }
            _temp += s;
            content[i] = _temp;
            continue;
        }

        if (ii > _stack.top())
        {
            _temp = "<ol><li>" + s.substr(ii + 1) + "</li>";
            _stack.push(ii);
        }
        else if (ii == _stack.top())
        {
            _temp = "<li>" + s.substr(ii + 1) + "</li>";
        }
        else
        {
            _temp = "";
            while (ii < top)
            {
                _temp += "<ol>";
                _stack.pop();
                top = _stack.top();
            }

            if (ii > _stack.top())
            {
                _temp += "<ol><li>" + s.substr(ii + 1) + "</li>";
                _stack.push(ii);
            }
            else if (ii == _stack.top())
            {
                _temp += "<li>" + s.substr(ii + 1) + "</li>";
            }
        }
        content[i] = _temp;
    }
}

int markdown::isBlockQuote(std::string s)
{
    std::regex re_blockquote("^>*\\s+.*");
    std::smatch sm;
    std::regex_match(s, sm, re_blockquote);

    if (sm.size() != 0)
    {
        auto idx = 0;
        while (s[idx] == '>')
        {
            idx++;
        }
        return idx;
    }
    else
    {
        return 0;
    }
}

std::string markdown::generateBlockQuote(std::string s, int number)
{
    std::string _temp1, _temp2;
    auto ii = number;
    while (ii > 0)
    {
        _temp1 += "<blockquote style=\"color:#8fbc8f\">";
        _temp2 += "</blockquote>";
        --ii;
    }
    return _temp1 + s.substr(number + 1) + _temp2;
}

int markdown::generateBlockQuote_S(std::string s)
{
    int cor_number = isBlockQuote(s);

    std::string result = "";
    if (mdtype == NORMAL && cor_number >= 1)
    {
        mdtype = INBLOCK;
        while (block_number < cor_number)
        {
            block_number++;
            result += "<blockquote>";
        }
        result += s.substr(cor_number);
        result += "<br />";

        output.push_back(result);
        return 1;
    }
    else if (mdtype == INBLOCK)
    {
        if (cor_number > block_number)
        {
            while (block_number < cor_number)
            {
                block_number++;
                result += "<blockquote>";
            }
        }
        else if (cor_number < block_number)
        {
            while (block_number > cor_number)
            {
                block_number--;
                result += "</blockquote>";
            }
        }
        result += s.substr(cor_number);
        result += "<br \>";
        if (block_number <= 0)
        {
            mdtype = NORMAL;
            block_number = 0;
        }
        output.push_back(result);
        return 1;
    }
    return 0;
}

bool markdown::isBr(std::string s)
{
    std::regex re_br("^[\\s\\t]*$");
    std::smatch sm;
    std::regex_match(s, sm, re_br);
    if (sm.size() > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int markdown::isCode(std::string s) {}
bool markdown::generateCode(std::string s) {}
bool markdown::generateTable(std::string) {}
std::vector<std::string> markdown::getTableElem(std::string s) {}

void markdown::generateFlow() {}

void markdown::tokenTool() {}
