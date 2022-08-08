/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-07 14:04:54
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-08 09:29:13
 * @FilePath: /c++/practices/json_parse_app/test.cpp
 * @Description: 注释信息
 */
#include "json_write.h"
#include <cmath>

int main()
{
    auto writer = new json_write();
    writer->StartArray();
    writer->StartObject();
    writer->KeyValue("name", "gzy");
    writer->KeyValue("age", "28");
    writer->EndObject();

    writer->StartObject();
    writer->Key("path");
    writer->StartArray();
    writer->Value("web");
    writer->Value("algorithm");
    writer->EndArray();

    writer->Key("short_array");
    writer->StartShortArray();
    writer->Value(1);
    writer->Value((uint64_t)0xabcdef123456);
    writer->Value(M_PI);
    writer->EndContainer();

    writer->EndObject();

    writer->EndArray();
}
