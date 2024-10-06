#include <iostream>
#include <regex>
#include <cstring>
#include <cctype>
#include <regex.h>
#include <algorithm>

#include "json_obj.h"

/*!
 * @brief Checks the correctness of the given a C-style json string of char * type.
 *
 * This function takes a C-style string as input, converts it into std::string and checks it`s correctness using overload
 *
 * @param str A C-style string representation of the structure.
 */

void check_json(char *str)
{
    std::string check_str(str);
    check_json(check_str);
}

/*!
 * @brief Checks the correctness of the given json string.
 *
 * This function takes a string as input and checks it`s correctness
 * If the string is not correct, it throws a std::invalid_argument().
 *
 * @param str The json string to check.
 * @throws std::invalid_argument() If the string uncorrected.
 */

void check_json(const std::string &str)
{
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

/*!
 * @brief Checks the type of the given word based on predefined regular expressions.
 *
 * This function takes a word as input and checks it against a set of predefined regular expressions
 * to determine its type. The function returns an integer representing the index of the matched type.
 * If no match is found, it throws a WrongTypeException.
 *
 * @param word The word to check.
 * @returns An integer as the index of the matched type.
 * @throws WrongTypeException If no matching type is found.
 */

int check_type(const std::string &word)
{
    const char *regex_type[] = {
        "^\"[A-Za-z0-9\\ ]+\"$",
        "^-?[0-9]+$",
        "^-?[0-9]+\\.[0-9]+$",
        "^(true|false)$",
        "^null$",
    };

    static std::regex patterns[] = {
        std::regex(regex_type[0]),
        std::regex(regex_type[1]),
        std::regex(regex_type[2]),
        std::regex(regex_type[3]),
        std::regex(regex_type[4]),
    };

    for (int i = 0; i < 5; ++i)
    {
        // static std::regex pattern(regex_type[i]);
        if (std::regex_match(word, patterns[i]))
        {
            return i;
        }
    }
    throw WrongTypeException();
}
