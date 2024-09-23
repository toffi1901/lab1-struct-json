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

int dio(char *&res, char *inputt, char *struct_name)
{
    char **types;
    char **names;
    try
    {
        types = new char *[strlen(inputt)];
        names = new char *[strlen(inputt)];
        if (!types || !names)
        {
            throw std::runtime_error("Error allocating memory\n");
        }
    }
    catch (std::runtime_error &e)
    {
        throw e;
    }
    int count = 0;
    try
    {
        count = get_struct(inputt, types, names);
        if (count == NO)
        {
            free_strings(names, count);
            delete[] types;
            delete[] names;
            return NO;
        }
        else
        {
            add_struct(res, types, names, struct_name, count);
        }
    }
    catch (const std::exception &e)
    {
        free_strings(types, count);
        delete[] types;
        delete[] names;
        throw e;
    }
    return OK;
}

int dio(std::string &res, std::string inputt, std::string struct_name)
{
    std::vector<std::string> types;
    std::vector<std::string> names;
    int count = get_struct(inputt, types, names);
    if (count == NO)
    {
        res = "";
        return NO;
    }
    else
    {
        add_struct(res, types, names, struct_name, count);
    }
    return OK;
}