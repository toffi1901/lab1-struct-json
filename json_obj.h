#ifndef JSON_H
#define JSON_H

#include <vector>

struct WrongTypeException
{
};

// ФУНКЦИИ ДЛЯ СТРКУТУРКИ

void add_struct(std::string &res, std::vector<std::string> &struct_types, const std::string &struct_name);
void get_struct(const std::string &inputt, std::vector<std::string> &struct_types);

std::vector<std::string> split(std::string &inputt);

// ПРОВЕРОЧКИ
int check_type(const std::string &word);
void check_json(char *str);
void check_json(const std::string &str);
void EmptyStrInput(const std::string &input);

// РАЗГОВАРИВАЮЩИЕ ФУНКЦИИ
void dio(char *&res, char *inputt, char *struct_name);
void dio(std::string &res, const std::string &inputt, const std::string &struct_name);

#endif