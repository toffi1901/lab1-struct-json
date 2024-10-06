#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

/*!
 * @class WrongTypeException
 * @brief Exception class for invalid type detection.
 *
 * This class is used to represent exceptions that occur when an invalid type is detected.
 */

class WrongTypeException : public std::exception
{
public:
    WrongTypeException() = default;
    virtual ~WrongTypeException() noexcept = default;
    /*!
     * This method provides a detailed error message indicating that an invalid type was detected.
     *
     * @returns A std::string containing the error message.
     */
    std::string get_message() const noexcept;
    /*!
     * @brief Returns a C-style string describing the exception.
     * @returns A C-style string containing the error message.
     * @note This method is marked as noexcept, meaning it will not throw exceptions.
     */
    const char *what() const noexcept;
};

#endif