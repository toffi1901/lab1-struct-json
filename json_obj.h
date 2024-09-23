#ifndef JSON_H
#define JSON_H

#include <vector>

enum ErrorCode
{
    REG_EX = -2,
    NO = -1,
    OK = 0,
};

// ФУНКЦИИ ДЛЯ СТРКУТУРКИ
// int check_name(char *word);
void add_struct(char *&res, char **struct_types, char **names, char *struct_name, int count);
void add_struct(std::string &res, std::vector<std::string> &struct_types, std::vector<std::string> &names, std::string struct_name, int count);

int get_struct(const char *str, char **struct_types, char **names);
int get_struct(std::string res, std::vector<std::string> &types, std::vector<std::string> &names);

std::vector<std::string> split(std::string &inputt, int &count);

// ПРОВЕРОЧКИ
int check_type(const std::string &word);
int check_type(char *word);
int check_json(char *str);
int check_json(std::string str);

// РАЗГОВАРИВАЮЩИЕ ФУНКЦИИ
int dio(char *&res, char *inputt, char *struct_name);
int dio(std::string &res, const std::string inputt, const std::string struct_name);

#endif