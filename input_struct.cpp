#include <iostream>
#include <cstring>
#include <vector>
#include <regex>

#include "json_obj.h"

void free_strings(char **strings, int count)
{
    std::for_each(strings, strings + count, [](char *str)
                  { delete[] str; });
}

void dio(char *&res, char *inputt, char *struct_name)
{
    std::string input_str(inputt);
    std::string str_name(struct_name);
    std::string str_res;
    dio(str_res, input_str, str_name);
    res = new char[str_res.size() + 1];
    std::strcpy(res, str_res.c_str());
}

void dio(std::string &res, const std::string &inputt, const std::string &struct_name)
{
    std::vector<std::string> types;
    get_struct(inputt, types);
    add_struct(res, types, struct_name);
}