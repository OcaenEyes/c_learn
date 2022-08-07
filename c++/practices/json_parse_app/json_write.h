/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-07 13:50:55
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-07 14:00:40
 * @FilePath: /c++/practices/json_parse_app/json_write.h
 * @Description: 注释信息
 */

#ifndef JSON_WRITE_H
#define JSON_WRITE_H
#include <stack>

enum ContainerType
{
    CONTAINERTYPE_ARRAY,
    CONTAINERTYPE_OBJECT
};

enum ContainerLayout
{
    CONTAINER_LAYOUT_INHERIT,
    CONTAINER_LAYOUT_MULTI_LINE,
    CONTAINER_LAYOUT_SINGLE_LINE
};

struct Container
{
    ContainerType type;
    ContainerLayout layout;
    bool isKey;
    int childCount;

    Container(ContainerType type,
              ContainerLayout layout) : type(type),
                                        layout(layout),
                                        isKey(false),
                                        childCount(0)
    {
    }
};

std::stack<Container *> depth;

class json_write
{
private:
    /* data */
public:
    json_write(/* args */);
    ~json_write();
};

#endif