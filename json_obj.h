#ifndef JSON_H
#define JSON_H

#include <vector>
#include "wrong_type_exception.h"

/*!
 * @file json_obj.h
 * @brief Header file containing declarations for various functions and classes.
 *
 * This file includes declarations for functions and classes that are used throughout the project.
 */

/*!
 * @brief Functions for generating a result.
 *
 * These functions transform the source data and form the result based on it.
 */
std::string add_struct(const std::vector<std::string> &struct_types, const std::string &struct_name);
std::vector<std::string> get_struct(const std::string &inputt);

std::vector<std::string> split(const std::string &inputt, const std::string &delim);
std::string trim(const std::string &str);
void free_strings(char **strings, int count);

char *dio(char *inputt, char *struct_name);
std::string dio(const std::string &inputt, const std::string &struct_name);

/*!
 * @brief Functions for checking the correctness of the data.
 */
int check_type(const std::string &word);
void check_json(char *str);
void check_json(const std::string &str);
bool check_input(std::string &inputt);

#endif