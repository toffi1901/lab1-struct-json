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

/*!
 * @brief Generates a string representation of a structure based on the input and structure name.
 *
 * This function takes C-style strings as input and structure name, converts them to std::string,
 * calls the std::string version of the function, and then returns the result as a C-style string.
 *
 * @param inputt The input C-style string containing the structure definition.
 * @param struct_name The name of the structure as a C-style string.
 * @returns A C-style string representation of the structure.
 */

char *dio(char *inputt, char *struct_name)
{
    std::string input_str(inputt);
    std::string str_name(struct_name);
    std::string str_res = dio(input_str, str_name);
    char *res = new char[str_res.size() + 1];
    std::strcpy(res, str_res.c_str());
    return res;
}
/*!
 * @brief Generates a string representation of a structure based on the input and structure name.
 * This function takes a strings as input and name of the struct.
 *
 * @param inputt The input string containing the structure definition.
 * @param struct_name The name of the structure.
 * @returns A string representation of the structure.
 */

std::string dio(const std::string &inputt, const std::string &struct_name)
{
    std::vector<std::string> types = get_struct(inputt);
    std::string res = add_struct(types, struct_name);
    return res;
}