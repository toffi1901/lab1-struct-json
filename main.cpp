#include <vld.h>
#include <iostream>
#include <regex>
#include <numeric>
#include <limits>

#include "json_obj.h"

bool check_input(std::string &inputt)
{
    std::getline(std::cin, inputt);
    if (std::cin.bad())
    {
        throw std::runtime_error("Broken input");
    }
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main()
{
    try
    {
        std::string struct_name;
        std::string inputt;
        bool validInput = false;
        do
        {
            try
            {
                std::cout << "Input struct name: ";
                bool check = check_input(struct_name);
                if (check == false)
                {
                    std::cout << "Input struct name: ";
                    check = check_input(struct_name);
                }
                std::cout << "Input json string\n";
                check = check_input(inputt);
                if (check == false)
                {
                    std::cout << "Input json string\n";
                    check = check_input(inputt);
                }
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
        std::string res = dio(inputt, struct_name);
        std::cout << res << std::endl;
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