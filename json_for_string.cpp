#include <iostream>
#include <regex>
#include <vector>
#include <string.h>
#include <algorithm>

#include "json_obj.h"

#define DELIM " ,:{}"

using namespace std;

std::vector<std::string> split(std::string &inputt, int &count)
{
    std::vector<std::string> tok;
    std::string::size_type start = 0;
    std::string::size_type end = inputt.find_first_of(DELIM, start);
    while (end != std::string::npos)
    {
        if (end != start)
        {
            tok.push_back(inputt.substr(start, end - start));
            count++;
        }
        start = end + 1;
        end = inputt.find_first_of(DELIM, start);
    }
    if (start < inputt.length())
    {
        tok.push_back(inputt.substr(start));
        count++;
    }
    return tok;
}

int get_struct(string inputt, vector<string> &struct_types, vector<string> &names)
{

    string str = inputt;
    const string types[] = {"char* ",
                            "long ",
                            "double ",
                            "bool ",
                            "void* "};

    int flag(1);
    int k(0), j(0), count(0);
    int check_res;
    vector<string> tok = split(str, count);
    for (int i = 0; i < count; ++i)
    {
        check_res = check_type(tok[i]);
        if (check_res == NO)
        {
            return check_res;
        }
        if (flag % 2 == 0)
        {
            struct_types.push_back(types[check_res]);
            k++;
        }
        else
        {
            string new_word = tok[i].substr(1, tok[i].size() - 2);
            names.push_back(new_word);
            j++;
        }
        flag++;
    }
    return k;
}

void add_struct(string &res, vector<string> &struct_types, vector<string> &names, string struct_name, int count)
{
    res += struct_name;
    res += "\n{\n";
    vector<string> combo;
    transform(struct_types.begin(), struct_types.begin() + count, names.begin(), back_inserter(combo), [](const string &type, const string &name)
              { return type + name; });
    for_each(combo.begin(), combo.begin() + count - 1, [](string &type)
             { type += ",\n"; });
    for_each(combo.begin(), combo.begin() + count, [&res](const string &str)
             { res += str; });
    res += "\n}";
}

/*void add_struct(string &res, vector<string> &struct_types, vector<string> &names, string struct_name, int count)
{
    res += struct_name;
    res += "\n{\n";
    for (int i = 0; i < count; ++i)
    {
        res += struct_types[i];
        res += names[i];
        (i != count - 1) ? (res += ",\n") : (res += "\n}");
    }
}*/