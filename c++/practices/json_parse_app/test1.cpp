/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-08 09:30:48
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-08 09:30:49
 * @FilePath: /c++/practices/json_parse_app/test1.cpp
 * @Description: 注释信息
 */
#include <iostream>
#include <cmath>
#include "json-writer.h"
using namespace std;

int main()
{
auto writer = new JsonWriter;
writer->StartArray ();

  writer->StartShortObject ();
    writer->KeyValue ("name", "shiyanlou1");
    writer->KeyValue ("age", 3);
  writer->EndObject ();

  writer->StartObject ();
    writer->KeyValue ("skills", "c++");
    writer->KeyValue ("skills","python");
    writer->KeyValue ("skills","php");
    writer->KeyValue ("skills","java");
    writer->KeyValue ("url", "http://shiyanlou.com");

    writer->Key ("path");
    writer->StartArray ();
      writer->Value ("web");
      writer->Value ("algorithm");
      writer->Value ("linux");
    writer->EndArray ();

    writer->Key ("short-array");
    writer->StartShortArray ();
      writer->Value (1);
      writer->Value ((uint64_t)0xabcdef123456);
      writer->Value (M_PI);
    writer->EndContainer ();

  writer->EndObject (),
  writer->Value (false);
writer->EndArray ();
}
