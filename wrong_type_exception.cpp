#include "wrong_type_exception.h"
#include <cstring>

std::string WrongTypeException::get_message() const noexcept
{
    return "Invalid type detected";
}

const char *WrongTypeException::what() const noexcept
{
    return "Invalid type detected";
}