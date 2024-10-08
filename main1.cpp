#include <vld.h>
#include <iostream>
#include <regex>
#include <readline/readline.h>

#include "json_obj.h"

int main()
{
    try
    {
        char *struct_name = NULL;
        char *inputt = NULL;
        bool validInput = false;
        do
        {
            try
            {
                struct_name = readline("Input struct name: ");
                inputt = readline("Input struct name: ");
                check_json(inputt);
                validInput = true;
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what() << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
                return 1;
            }
        } while (!validInput);
        char *res = NULL;
        res = dio(inputt, struct_name);
        std::cout << res << std::endl;
        delete[] res;
    }
    catch (WrongTypeException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}