// #include <vld.h>
#include <iostream>
#include <regex>

#include "json_obj.h"

int main()
{
    std::string struct_name;
    // char *struct_name;
    std::cout << "Input struct name: ";
    try
    {
        std::getline(std::cin, struct_name);
        std::string inputt;
        std::cout << "Input json string\n";
        std::getline(std::cin, inputt);
        int check_str = check_json(inputt);
        if (check_str != OK)
        {
            std::cout << "Error input, try again\n"
                      << std::endl;
            inputt.clear();
            check_str = check_json(inputt);
            std::getline(std::cin, inputt);
        }
        std::string res;
        int r = dio(res, inputt, struct_name);
        if (r == NO)
        {
            std::cout << "This format doesn`t match\n"
                      << std::endl;
        }
        std::cout << res << std::endl;
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