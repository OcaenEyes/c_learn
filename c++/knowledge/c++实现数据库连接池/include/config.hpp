/*
 * @Author: OCEAN.GZY
 * @Date: 2023-12-27 08:49:23
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-12-27 12:03:36
 * @FilePath: /c++/knowledge/c++实现数据库连接池/include/config.hpp
 * @Description: 注释信息
 *
 * 借鉴学习自：https://blog.csdn.net/ljjjjjjjjjjj/article/details/125873100
 *
 */
#pragma once

#include <string>
#include <map>
#include <fstream>

class INIConfig
{
private:
    std::map<std::string, std::map<std::string, std::string>> m_mapConfig;

    bool isSpace(char c)
    {
        if (c == ' ' || c == '\t')
        {
            return true;
        }
        return false;
    }

    bool isCommentChar(char c)
    {
        if (c == '#')
        {
            return true;
        }
        return false;
    }

    void trim(std::string &str)
    {
        if (str.empty())
        {
            return;
        }
        int i, start_pos, end_pos;
        // 左边去空格
        for (i = 0; i < str.size(); i++)
        {
            if (!isSpace(str[i]))
            {
                start_pos = i;
                break;
            }
        }

        if (i == str.size())
        {
            str = "";
            return;
        }
        // 右边去空格
        for (i = str.size() - 1; i >= 0; i--)
        {
            if (!isSpace(str[i]))
            {
                end_pos = i;
                break;
            }
        }

        str = str.substr(start_pos, end_pos - start_pos + 1);
    }

    bool analyseLine(const std::string &line, std::string &section, std::string &key, std::string &value)
    {
        if (line.empty())
        {
            return false;
        }

        int start_pos = 0, end_pos = line.size() - 1, pos, s_start_pos, s_end_pos;
        /**
         * string::find()函数：是一个字符或字符串查找函数，该函数有唯一的返回类型，即string::size_type，即一个无符号整形类型，可能是整数也可能是长整数。如果查找成功，返回按照查找规则找到的第一个字符或者子串的位置；
         *      如果查找失败，返回string::npos,即-1（当然打印出的结果不是-1，而是一个很大的数值，那是因为它是无符号的）
         * string::npos静态成员常量：是对类型为size_t的元素具有最大可能的值。当这个值在字符串成员函数中的长度或者子长度被使用时，该值表示“直到字符串结尾”。作为返回值他通常被用作表明没有匹配。
         * string::npos是这样定义的：static const size_type npos = -1;
         * 因为string::size_type描述的是size，故需为无符号整数型类别。因为缺省配置为size_t作为size_type，于是-1被转换为无符号整数类型，npos也就成为了该类别的最大无符号值。不过实际值还是取决于size_type的实际定义类型，即无符号整型（unsigned int）的-1与无符号长整型（unsigned long）的-1是不同的
         */

        if ((pos = line.find('#')) != -1)
        {
            if (pos == 0)
            {
                return false;
            }
            end_pos = pos - 1;
        }

        if (((s_start_pos = line.find("[")) != -1) && (s_end_pos = line.find("]")) != -1)
        {
            section = line.substr(s_start_pos + 1, s_end_pos - 1);
            return true;
        }

        std::string new_line = line.substr(start_pos, end_pos - start_pos + 1);
        if ((pos = new_line.find('=')) == -1)
        {
            return false;
        }
        std::string key = new_line.substr(0, pos);
        std::string value = new_line.substr(pos + 1);
        trim(key);
        if (key.empty())
        {
            return false;
        }
        trim(value);
        if ((pos = value.find('\r')) > 0)
        {
            value.replace(pos, 1, "");
        }
        if ((pos = value.find('\n')) > 0)
        {
            value.replace(pos, 1, "");
        }
        return true;
    }

public:
    INIConfig(/* args */) {}
    ~INIConfig() {}

    bool readConfig(const std::string &strFileName)
    {
        m_mapConfig.clear();
        std::ifstream ifs(strFileName.c_str());
        if (!ifs.is_open())
        {
            return false;
        }
        std::string line, key, value, section;
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::map<std::string, std::string>>::iterator it_section;
        while (std::getline(ifs, line))
        {
            if (analyseLine(line, section, key, value))
            {
                it_section = m_mapConfig.find(section);
                if (it_section != m_mapConfig.end())
                {
                    k_v[key] = value;
                    m_mapConfig[section] = k_v;
                }
                else
                {
                    k_v[key].clear();
                    m_mapConfig.insert(std::make_pair(section, k_v));
                }
            }
        }

        return true;
    }
};