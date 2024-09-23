#include <iostream>
#include <regex>
#include <cstring>
#include <cctype>
#include <regex.h>

#include "json_obj.h"

int check_json(char *str)
{
    int len = strlen(str);
    if (str[0] != '{' || str[len - 1] != '}')
    {
        return NO;
    }

    int i = 1;
    while (i < len - 1)
    {

        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] != '"')
        {
            return NO;
        }
        i++;
        while (str[i] != '"' && i < len)
            i++;
        if (str[i] != '"')
        {
            return NO;
        }
        i++;
        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] != ':')
        {
            return NO;
        }
        i++;
        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"' && i < len)
                i++;
            if (str[i] != '"')
                return NO;
            i++;
        }
        else if (isdigit(str[i]) || str[i] == '-' || str[i] == '.')
        {
            while (isdigit(str[i]) || str[i] == '.' || str[i] == '-')
                i++;
        }
        else if (strncmp(&str[i], "true", 4) == 0 || strncmp(&str[i], "false", 5) == 0 || strncmp(&str[i], "null", 4) == 0)
        {
            i += (strncmp(&str[i], "true", 4) == 0) ? 4 : (strncmp(&str[i], "false", 5) == 0) ? 5
                                                                                              : 4;
        }
        else
        {
            return NO;
        }
        while (isspace(str[i]))
        {
            i++;
        }
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
            return NO;
        }
    }

    return OK;
}

int check_json(std::string str)
{
    int len = str.length();
    if (str[0] != '{' || str[len - 1] != '}')
    {
        return NO;
    }

    int i = 1;
    while (i < len - 1)
    {

        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] != '"')
        {
            return NO;
        }
        i++;
        while (str[i] != '"' && i < len)
            i++;
        if (str[i] != '"')
        {
            return NO;
        }
        i++;
        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] != ':')
        {
            return NO;
        }
        i++;
        while (isspace(str[i]))
        {
            i++;
        }
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"' && i < len)
                i++;
            if (str[i] != '"')
                return NO;
            i++;
        }
        else if (isdigit(str[i]) || str[i] == '-' || str[i] == '.')
        {
            while (isdigit(str[i]) || str[i] == '.' || str[i] == '-')
                i++;
        }
        else if (strncmp(&str[i], "true", 4) == 0 || strncmp(&str[i], "false", 5) == 0 || strncmp(&str[i], "null", 4) == 0)
        {
            i += (strncmp(&str[i], "true", 4) == 0) ? 4 : (strncmp(&str[i], "false", 5) == 0) ? 5
                                                                                              : 4;
        }
        else
        {
            return NO;
        }
        while (isspace(str[i]))
        {
            i++;
        }
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
            return NO;
        }
    }

    return OK;
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
    return NO;
}

int check_type(char *word)
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
    return NO;
}