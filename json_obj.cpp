#include <iostream>
#include <cstring>
#include <algorithm>

#include "json_obj.h"

#define DELIM ": ,"

using namespace std;

int get_struct(const char *inputt, char **struct_types, char **names)
{
    char *str = strdup(inputt);
    const char *types[] = {"char* ",
                           "long ",
                           "double ",
                           "bool ",
                           "void* "};

    char *word = strtok(str, DELIM);
    int flag(1);
    int i(0), j(0);
    int check_res;
    while (word != NULL)
    {
        check_res = check_type(word);
        if (check_res == NO)
        {
            return check_res;
        }
        if (flag % 2 == 0)
        {
            int type = check_res;
            struct_types[i] = new char[strlen(types[type])]{};
            strcpy(struct_types[i++], types[type]);
        }
        else
        {
            names[j] = new char[strlen(word) - 1]{};
            char *new_word = new char[strlen(word) - 1];
            strncpy(new_word, word + 1, strlen(word) - 2);
            strcpy(names[j++], new_word);
            delete[] new_word;
        }
        flag++;
        word = strtok(NULL, DELIM);
    }
    free(str);
    return i;
}

void add_struct(char *&res, char **struct_types, char **names, char *struct_name, int count)
{
    strcat(res, struct_name);
    strcat(res, "\n{\n");
    for (int i = 0; i < count; ++i)
    {
        strcat(res, struct_types[i]);
        strcat(res, names[i]);
        (i != count - 1) ? strcat(res, ",\n") : strcat(res, "\n}");
    }
}
