/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-30 07:19:32
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-02-02 07:28:32
 * @FilePath: /c++/practices/mdparser/src/markdown.cpp
 * @Description: 注释信息
 */
#include "markdown.h"

void markdown::setTitle(std::string _title)
{
    std::cout << "传入的文件名字title:" << _title << std::endl;
    ;
    title = _title;
}

int markdown::getContent(std::vector<std::string> &_content)
{
    content = _content;
    content_length = _content.size();
    std::cout << "传入的文件内容长度是:" << _content.size() << std::endl;
    return 0;
}

void markdown::outputMarkdown(std::vector<std::string> &_detail)
{
    for (auto v : output)
    {
        _detail.push_back(v);
    }
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

        if (generateBlockQuote_S(s) == 1)
        {
        }
        else if (generateCode(s) == 1)
        {
        }
        else if (generateTable(s) == 1)
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
    std::cout << "执行generatePre之后的 output的长度是：" << output.size() << std::endl;
    return 0;
}

int markdown::generateCore()
{
    output.clear();
    aligns.clear();
    for (int i = 0; i < 10; ++i)
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
                            <div id=\"placeholder\">");

    output.push_back("<script type=\"text/x-mathjax-config\"> MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\\\(','\\\\)']]}});</script>");
    output.push_back("<script type=\"text/javascript\" src=\"./thirds/custom-mathjax.min.js\" id=\"MathJax-script\">");
    output.push_back("</script>");

    output.push_back("<script type=\"text/javascript\" src=\"./thirds/raphael.js\">");
    output.push_back("</script>");

    output.push_back("<script type=\"text/javascript\" src=\"./thirds/flowchart.js\">");
    output.push_back("</script>");

    output.push_back("<link rel=\"stylesheet\" href=\"./thirds/css/github.css\">");

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
            _temp = "<li>" + s.substr(ii + 1) + "</li>";
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
        result += "<br />";
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

int markdown::isCode(std::string s) { return 0; }
bool markdown::generateCode(std::string s)
{
    std::regex re_code("^\\s*```\\s*[a-zA-Z1-9\\+\\.]*\\s*$");
    std::regex re_s("\\s");
    std::regex re_t("\\t");

    std::smatch sm;
    std::regex_match(s, sm, re_code);

    std::string _temp1, _temp2;

    if (mdtype == NORMAL && sm.size() > 0)
    {
        mdtype = INCODE;
        output.push_back("<code><pre>");
        return 1;
    }
    else if (mdtype == INCODE && sm.size() > 0)
    {
        mdtype = NORMAL;
        output.push_back("</pre></code>");
        return 1;
    }
    else if (mdtype == INCODE)
    {
        std::regex_replace(std::back_inserter(_temp1), s.begin(), s.end(), re_s, "&nbsp");
        std::regex_replace(std::back_inserter(_temp2), s.begin(), s.end(), re_t, "&nbsp&nbsp&nbsp&nbsp");
        _temp1 = "<span>" + _temp2 + "</span><br />";
        output.push_back(_temp1);
        return 1;
    }
    else
    {
        return 0;
    }
}
bool markdown::generateTable(std::string s)
{
    std::regex re_table("\\|(.*)\\|");
    std::regex re_rep("\\|");
    std::smatch sm;

    std::regex_match(s, sm, re_table);
    std::string result = "";
    std::vector<std::string> elem;

    // std::cout << "该行输入s是：" << s << std::endl;
    // std::cout << "此时mdtype是：" << mdtype << std::endl;

    if (mdtype == NORMAL && sm.size() > 0)
    {
        elem = getTableElem(s);
        result += "<table align=\"center\" cellspacing=\"0\" cellpadding=\"5\">";
        result += "<tr>";

        for (auto e : elem)
        {
            result += "<th>" + e + "</th>";
        }

        result += "</tr>";

        table_number = static_cast<int>(elem.size());

        mdtype = TABLE_FMT;
        output.push_back(result);
        return 1;
    }
    else if (mdtype == TABLE_FMT && sm.size() > 0)
    {
        elem = getTableElem(s);
        for (auto ii = 0; ii < table_number; ++ii)
        {
            std::regex_match(elem[ii], sm, std::regex("\\:\\-*"));
            if (sm.size() > 0)
                aligns[ii] = "left";
            std::regex_match(elem[ii], sm, std::regex("\\:\\-*\\:"));
            if (sm.size() > 0)
                aligns[ii] = "center";
            std::regex_match(elem[ii], sm, std::regex("\\-*\\:"));
            if (sm.size() > 0)
                aligns[ii] = "right";
        }
        mdtype = INTABLE;
        return 1;
    }
    else if (mdtype == INTABLE && sm.size() > 0)
    {
        elem = getTableElem(s);
        std::cout << "************" << std::endl;
        std::cout << "当是在表格内部时,s是：" << s << std::endl;
        result += "<tr>";
        for (auto ii = 0; ii < table_number; ++ii)
        {
            result += "<td align=\"" + aligns[ii] + "\">" + elem[ii] + "</td>";
            std::cout << "当是在表格内部时,elem[ii]是：" << elem[ii] << std::endl;
        }

        result += "</tr>";
        output.push_back(result);
        return 1;
    }
    else if ((mdtype == INTABLE || mdtype == TABLE_FMT) && sm.size() == 0)
    {
        table_number = 0;
        mdtype = NORMAL;
        result += "</table>" + s;
        output.push_back(result);
        return 1;
    }
    return 0;
}
std::vector<std::string> markdown::getTableElem(std::string s)
{
    std::vector<std::string> result;
    std::string _temp = "";

    for (auto c : s)
    {
        if (c == '|')
        {
            result.push_back(_temp);
            _temp.clear();
        }
        else
        {
            _temp += c;
        }
    }

    result.erase(result.begin());
    return result;
}

void markdown::generateFlow()
{
    auto flow_number = 0;
    std::regex re_flow_start("^\\[flow\\]&");
    std::regex re_flow_end("^\\[!flow\\]&");

    std::smatch sm;

    for (auto ii = 0; ii < content.size(); ++ii)
    {
        std::regex_search(content[ii], sm, re_flow_start);
        if (sm.size() > 0)
        {
            ++flow_number;
            content[ii] = "<div id=\"flow" + std::to_string(flow_number) + "\"> </div>";
            auto jj = ii + 1;
            content[ii] += "<script>var diagram = flowchart.parse(";
            std::regex_match(content[jj], sm, re_flow_end);
            while (jj < content.size() && sm.size() == 0)
            {
                content[ii] += "'" + content[jj] + "\\n'+";
                content.erase(content.begin() + jj);
                std::regex_match(content[jj], sm, re_flow_end);
            }
            content[ii] += "' ')diagram.drwSVG('flow" + std::to_string(flow_number) + "');</script>";
            content.erase(content.begin() + jj);
        }
    }
}

void markdown::tokenTool()
{
    std::string _temp1, _temp2;
    std::regex re_lt("<");
    std::regex re_and("&");
    std::regex re_link("\\[(.*)\\]\\((.*)\\)");
    std::regex re_sup("\\[(.*)\\]\\[(.*)\\]");
    std::regex re_img("!\\[(.*)\\]\\((.*)\\)");
    std::regex re_i("\\*([^\\*]+)\\*");
    std::regex re_S("\\~\\~([^\\~\\~]+)\\~\\~");
    std::regex re_b("\\*\\*([^\\*\\*]+)\\*\\*");
    std::regex re_math("\\$([^\\$]*)\\$");
    std::regex re_code("```(.*)```");

    std::smatch sm;

    for (int i = 0; i < content.size(); ++i)
    {
        _temp1 = content[i];
        _temp1.insert(_temp1.begin(), ' ');

        // _temp2.clear();
        // std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), re_and, "&amp;");

        // _temp1.clear();
        // std::regex_replace(std::back_inserter(_temp1), _temp2.begin(), _temp2.end(), re_lt, "&lt;");

        //  _temp2.clear();
        // std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), std::regex("\\\\&amp;"), "&");

        // _temp1.clear();
        // std::regex_replace(std::back_inserter(_temp1), _temp2.begin(), _temp2.end(), std::regex("\\\\&lt;"), "<");

        _temp2.clear();
        std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), re_link, "<a href=\"$2\" target=\"_blank\" >$1</a>");

        _temp1.clear();
        std::regex_replace(std::back_inserter(_temp1), _temp2.begin(), _temp2.end(), re_img, "<img src=\"$2\"align=\"middle\" >");

        _temp2.clear();
        std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), re_sup, "$1<sup>$2</sup>;");

        _temp1.clear();
        std::regex_replace(std::back_inserter(_temp1), _temp2.begin(), _temp2.end(), re_b, "<b>$1</b>");

        _temp2.clear();
        std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), re_S, "<s>$1</s>");

        _temp1.clear();
        std::regex_replace(std::back_inserter(_temp1), _temp2.begin(), _temp2.end(), re_i, "<i>$1</i>");

        _temp2.clear();
        std::regex_replace(std::back_inserter(_temp2), _temp1.begin(), _temp1.end(), re_code, "<code>$1</code>");

        std::regex_match(_temp2, sm, re_math);

        if (sm.size() > 0)
        {
            needMathJax = 1;
        }

        _temp2.erase(_temp2.begin());
        content[i] = _temp2;
    }
}

int markdown::isToc(std::string s)
{
    std::regex re_toc("\\[TOC\\]");
    std::smatch sm;
    std::regex_match(s, sm, re_toc);

    if (sm.size() > 0)
    {
        needToc = 1;
        toc_content = s;
        return 1;
    }
    return 0;
}

void markdown::generateToc()
{
    auto deep = 0;
    auto toc_position = std::find(output.begin(), output.end(), toc_content); // 从begin到end 查找 toc_content

    if (toc_position == output.end())
    {
        return;
    }

    for (auto list : tocs)
    {
        if (list.deep > deep)
        {
            while (deep < list.deep)
            {
                toc_string.push_back("<ol style=\"line-height:80%\">");
                deep++;
            }
            toc_string.push_back("<li><a href=\"#" + list.name + "\">" + list.name + "</a></li>");
        }
        else if (list.deep == deep)
        {
            toc_string.push_back("<li><a href=\"#" + list.name + "\">" + list.name + "</a></li>");
        }
        else
        {
            while (deep > list.deep)
            {
                toc_string.push_back("</>");
                deep--;
            }
            toc_string.push_back("<li><a href=\"#" + list.name + "\">" + list.name + "</a></li>");
        }
    }
    while (deep > 0)
    {
        toc_string.push_back("</ol>");
        deep--;
    }
    for (int ii = static_cast<int>(toc_string.size()) - 1; ii >= 0; ii--)
    {
        output.insert(toc_position + 1, toc_string[ii]);
    }
}

markdown::markdown(/* args */)
{
    needMathJax = 0;
    mdtype = NORMAL;
}

markdown::~markdown()
{
}