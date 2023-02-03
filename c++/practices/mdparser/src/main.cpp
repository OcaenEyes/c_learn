/*
 * @Author: OCEAN.GZY
 * @Date: 2023-01-30 03:27:09
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-02-03 13:17:20
 * @FilePath: /c++/practices/mdparser/src/main.cpp
 * @Description: 注释信息
 */

#include "markdown.h"

int checkInput(std::string name)
{
    std::smatch sm;
    std::regex_match(name, sm, std::regex(".*[(md)(markdown)(mkd)(mdown)]"));
    return static_cast<int>(sm.size());
}

int main(int argc, const char *argv[])
{
    markdown _markdown;
    std::vector<std::string> cmds;
    std::vector<std::string> c;
    std::vector<std::string> outputs;
    std::string buff;
    std::string from;
    std::string dest = "out.html";

    std::cout << "传入参数个数是：" << argc << std::endl;

    for (int i = 0; i < argc; i++)
    {
        std::cout << "传入参数-" << i << "-是：" << argv[i] << std::endl;
    }

    if (argc < 2)
    {
        std::cout << "参数不足" << std::endl;
        return -1;
    }
    if (checkInput(argv[1]))
    {
        from = argv[1];
    }
    else
    {
        std::cout << "不是一个markdown文件" << std::endl;
        return 1;
    }

    if (argc > 2)
    {
        dest = argv[2];
    }

    std::ifstream file;
    file.open(from);
    if (!file)
    {
        std::cout << "文件打开失败" << std::endl;
        return -1;
    }

    while (std::getline(file, buff))
    {
        std::cout << "读取到的文件是：" << buff << std::endl;
        c.push_back(buff);
    }

    c.push_back("");
    _markdown.setTitle(from);
    _markdown.getContent(c);
    _markdown.generateCore();
    _markdown.outputMarkdown(outputs);

    std::ofstream fout;
    fout.open(dest);
    for (auto s : outputs)
    {
        fout << s << std::endl;
    }

    return 0;
}

// int main()
// {
//     markdown _markdown;
//     std::vector<std::string> outputs;
//     std::string input;
//     std::vector<std::string> inputs;
//     while (true)
//     {
//         std::cin >> input;
//         outputs.clear();
//         inputs.push_back(input);
//         inputs.push_back("");
//         _markdown.getContent(inputs);
//         _markdown.generateCore();
//         _markdown.outputMarkdown(outputs);
//         std::cout << outputs.size() << std::endl;
//         std::cout << outputs.at(0) << std::endl;
//         for (int i = 0; i < static_cast<int>(outputs.size()); i++)
//         {
//             std::cout << outputs.at(i) << std::endl;
//         }
//     }
//     return 0;
// }