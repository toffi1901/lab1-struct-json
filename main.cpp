#include <vld.h>
#include <iostream>
#include <regex>

#include "json_obj.h"

int main()
{
    try
    {
        std::string struct_name;
        std::string inputt;
        std::cout << "Input struct name: ";
        std::getline(std::cin, struct_name);
        EmptyStrInput(struct_name);
        bool validInput = false;
        do
        {
            try
            {
                std::cout << "Input json string\n";
                std::getline(std::cin, inputt);
                check_json(inputt);
                validInput = true;
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what() << std::endl;
            }
        } while (!validInput);
        std::string res;
        dio(res, inputt, struct_name);
        std::cout << res << std::endl;
    }
    catch (WrongTypeException &e)
    {
        std::cout << "Error word type!\n"
                  << std::endl;
    }
    catch (const std::regex_error &e)
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