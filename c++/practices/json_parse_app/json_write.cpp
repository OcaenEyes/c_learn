/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-07 13:54:40
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-08 09:39:05
 * @FilePath: /c++/practices/json_parse_app/json_write.cpp
 * @Description: 注释信息
 */

#include "json_write.h"

void json_write::Indent()
{
    for (int i = 0, s = initialIndentDepth + depth.size(); i < s; i++)
    {
        Write() << indent;
    }
}

void json_write::StartChild(bool isKey)
{
    if (depth.size() == 0)
    {
        if (initialIndentDepth > 0)
        {
            Indent();
        }
        return;
    }

    Container *container = depth.top();
    if (container->childCount > 0 &&
        (container->type == CONTAINERTYPE_ARRAY || (container->type == CONTAINERTYPE_OBJECT && !container->isKey)))
    {
        Write() << ",";
        if (container->layout == CONTAINER_LAYOUT_SINGLE_LINE)
        {
            Write() << containerPadding;
        }
        else
        {
            Write() << std::endl;
            Indent();
        }
    }
    else if (container->childCount == 0)
    {
        Write() << containerPadding;
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE)
        {
            Write() << std::endl;
            Indent();
        }
    }

    container->isKey = isKey;
    container->childCount++;
}

void json_write::Key(const char *key)
{
    StartChild(true);
    WriteString(key);
    Write() << keyPaddingLeft << ":" << keyPaddingRight;
}

void json_write::NullValue()
{
    StartChild();
    Write() << "null";
}

void json_write::Value(const char *value)
{
    StartChild();
    WriteString(value);
}

void json_write::Value(std::string value)
{
    StartChild();
    WriteString(value.c_str());
}

void json_write::Value(bool value)
{
    StartChild();
    Write() << (value ? "true" : "false");
}

void json_write::StartContainer(ContainerType type, ContainerLayout layout)
{
    if (forceDefaultContainerLayout)
    {
        layout = defaultContainerLayout;
    }
    else if (layout == CONTAINER_LAYOUT_INHERIT)
    {
        if (depth.size() > 0)
        {
            layout = depth.top()->layout;
        }
        else
        {
            layout = defaultContainerLayout;
        }
    }

    StartChild();
    depth.push(new Container(type, layout));
    Write() << (type == CONTAINERTYPE_OBJECT ? '{'
                                             : '[');
}

void json_write::EndContainer()
{
    Container *container = depth.top();
    depth.pop();

    if (container->childCount > 0)
    {
        if (container->layout == CONTAINER_LAYOUT_MULTI_LINE)
        {
            Write() << std::endl;
            Indent();
        }
        else
        {
            Write() << containerPadding;
        }
    }

    Write() << (container->type == CONTAINERTYPE_OBJECT ? '}' : ']');

    delete container;
}

void json_write::WriteEscapedChar(char c)
{
    switch (c)
    {
    case '"':
        Write() << "\\\"";
        break;
    case '\\':
        Write() << "\\\\";
        break;
    case '\b':
        Write() << "\\b";
        break;
    case '\f':
        Write() << "\\f";
        break;
    case '\n':
        Write() << "\\n";
        break;
    case '\r':
        Write() << "\\r";
        break;
    case '\t':
        Write() << "\\t";
        break;
    default:
        Write() << c;
        break;
    }
}

void json_write::WriteString(const char *str)
{
    Write() << "\"";
    for (int i = 0; str[i] != 0; i++)
    {
        WriteEscapedChar(str[i]);
    }
    Write() << "\"";
}

json_write::~json_write()
{
}
