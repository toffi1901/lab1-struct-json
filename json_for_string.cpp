#include <iostream>
#include <regex>
#include <vector>
#include <string.h>
#include <algorithm>
#include <numeric>

#include "json_obj.h"

/*!
 * @param inputt The input string containing the structure definition.
 * @param delim Delimiters used to separate a string.
 * @returns A vector of strings.
 */

std::vector<std::string> split(const std::string &inputt, const std::string &delim)
{
    std::vector<std::string> tok;
    std::string::size_type start = 0;
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

/*!
 * @param str The string in which spaces will be removed.
 * @returns A string without spaces.
 */

std::string trim(const std::string &str)
{
    auto first = str.find_first_not_of(" ");
    auto last = str.find_last_not_of(" ");
    if (first == str.npos)
    {
        return "";
    }
    return str.substr(first, last - first + 1);
}

/*!
 * @param inputt The input string containing the structure definition.
 * @returns A vector containing data types and their names.
 * @throws WrongTypeException,If the element of vector uncorrected.
 */

std::vector<std::string> get_struct(const std::string &inputt)
{
    const std::string types[] = {"char* ",
                                 "long ",
                                 "double ",
                                 "bool ",
                                 "void* "};
    std::string aux_type;
    std::string delim = "{},";
    std::string str = trim(inputt);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::vector<std::string> tok = split(str, delim);
    std::vector<std::string> struct_types(tok.size());
    std::transform(tok.begin(), tok.end(), struct_types.begin(), [&types](const std::string &val)
                   { auto parts = split(val, ":");
                   if (parts.size() != 2){
                        throw WrongTypeException();
                   }
                    auto key = parts[0];
                    auto value = parts[1];                
                   auto aux_key = key.substr(1, key.size() - 2);   
                   auto aux_type = types[check_type(value)]; 
                   auto r =  aux_type + aux_key;                              
                   return r; });
    return struct_types;
}

/*!
 * @brief This function generates the result.
 *
 * @param struct_types A vector containing data types and their names.
 * @param struct_name The name of the structure.
 * @returns An integer as the result of connecting the elements of the vector.
 */

std::string add_struct(const std::vector<std::string> &struct_types, const std::string &struct_name)
{
    std::string res = struct_name + "\n{\n";
    res += std::accumulate(struct_types.begin(), struct_types.end(), std::string(), [](const auto &l, const auto &r)
                           { return l + r + ";\n"; });
    res += "};";
    return res;
}
