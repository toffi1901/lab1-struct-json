#include <iostream>
#include <regex>
#include <cstring>
#include <cctype>
#include <regex.h>
#include <algorithm>

#include "json_obj.h"

void EmptyStrInput(const std::string &input)
{
    if (input.empty())
    {
        std::cout << "Error input, try again: " << input << std::endl;
        throw std::invalid_argument("Input is empty");
    }
}

void check_json(char *str)
{
    std::string check_str(str);
    check_json(check_str);
}

void check_json(const std::string &str)
{
    int len = str.length();
    int start = str.find_first_not_of(" ");
    int end = str.find_last_not_of(" ");
    if ((str[start] != '{' || str[end] != '}'))
    {
        throw std::invalid_argument("Invalid input!");
    }
    int i = start + 1;
    while (i < end)
    {

        i = str.find_first_not_of(" ", i);
        if (str[i] != '"')
        {
            throw std::invalid_argument("Invalid input!");
        }
        i++;
        while (str[i] != '"' && i < end)
        {
            i++;
        }
        if (str[i] != '"')
        {
            throw std::invalid_argument("Invalid input!");
        }
        i++;
        i = str.find_first_not_of(" ", i);
        if (str[i] != ':')
        {
            throw std::invalid_argument("Invalid input!");
        }
        i++;
        i = str.find_first_not_of(" ", i);
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"' && i < end)
            {
                i++;
            }
            if (str[i] != '"')
            {
                throw std::invalid_argument("Invalid input!");
            }
            i++;
        }
        else if (isdigit(str[i]) || str[i] == '-' || str[i] == '.')
        {
            while (isdigit(str[i]) || str[i] == '.' || str[i] == '-')
            {
                i++;
            }
        }
        else if (strncmp(&str[i], "true", 4) == 0 || strncmp(&str[i], "false", 5) == 0 || strncmp(&str[i], "null", 4) == 0)
        {
            i += (strncmp(&str[i], "true", 4) == 0) ? 4 : (strncmp(&str[i], "false", 5) == 0) ? 5
                                                                                              : 4;
        }
        else
        {
            throw std::invalid_argument("Invalid input!");
        }
        i = str.find_first_not_of(" ", i);
        if (str[i] == ',')
        {
            i++;
        }
        else if (str[i] == '}')
        {
            break;
        }
        else
        {
            throw std::invalid_argument("Invalid input!");
        }
    }
}

int check_type(const std::string &word)
{
    const char *regex_type[] = {
        "^\"[A-Za-z0-9\\ ]+\"$",
        "^-?[0-9]+$",
        "^-?[0-9]+\\.[0-9]+$",
        "^(true|false)$",
        "^null$",
    };
    for (int i = 0; i < 5; ++i)
    {
        std::regex pattern(regex_type[i]);
        if (std::regex_match(word, pattern))
        {
            return i;
        }
    }
    throw WrongTypeException();
}
