#include <iostream>
#include <regex>
#include <vector>
#include <string.h>
#include <algorithm>
#include <numeric>

#include "json_obj.h"

std::vector<std::string> split(std::string &inputt)
{
    std::vector<std::string> tok;
    std::string::size_type start = 0;
    std::string delim = " ,:{}";
    std::string::size_type end = inputt.find_first_of(delim, start);
    while (end != std::string::npos)
    {
        if (end != start)
        {
            tok.push_back(inputt.substr(start, end - start));
        }
        start = end + 1;
        end = inputt.find_first_of(delim, start);
    }
    if (start < inputt.length())
    {
        tok.push_back(inputt.substr(start));
    }
    return tok;
}

void get_struct(const std::string &inputt, std::vector<std::string> &struct_types)
{

    std::string str = inputt;
    const std::string types[] = {"char* ",
                                 "long ",
                                 "double ",
                                 "bool ",
                                 "void* "};
    std::string aux_type;
    std::string aux_name;
    std::vector<std::string> tok = split(str);
    for (int i = 0; i < tok.size(); ++i)
    {

        int check_res = check_type(tok[i]);
        if (i % 2 == 1)
        {
            aux_type = types[check_res];
            aux_type += aux_name;
            struct_types.push_back(aux_type);
            aux_type.clear();
        }
        else
        {
            std::string new_word = tok[i].substr(1, tok[i].size() - 2);
            aux_name = new_word;
        }
    }
}

void add_struct(std::string &res, std::vector<std::string> &struct_types, const std::string &struct_name)
{
    res += struct_name;
    res += "\n{\n";
    std::for_each(struct_types.begin(), struct_types.end() - 1, [](std::string &type)
                  { type += ",\n"; });
    res += std::accumulate(struct_types.begin(), struct_types.end(), std::string());
    res += "\n}";
}
