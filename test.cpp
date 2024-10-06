#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>
#include "json_obj.h"

TEST(splitTest, ValidInput)
{
    std::vector<std::string> tokens;
    std::string inputt = "{\"key\" : \"value\"}";
    tokens = split(inputt, "{}: ");
    EXPECT_THAT(tokens, testing::ElementsAre("\"key\"", "\"value\""));
}

TEST(check_typeTest, InvalidChar)
{
    const std::string word = "word";
    EXPECT_THROW(check_type(word), WrongTypeException);
}

TEST(check_typeTest, ValidChar)
{
    const std::string word = "\"word\"";
    int res = check_type(word);
    EXPECT_EQ(res, 0);
}

TEST(check_typeTest, ValidLong)
{
    const std::string word = "123";
    int res = check_type(word);
    EXPECT_EQ(res, 1);
}

TEST(check_typeTest, ValidDouble)
{
    const std::string word = "1.3";
    int res = check_type(word);
    EXPECT_EQ(res, 2);
}

TEST(check_typeTest, ValidBool)
{
    const std::string word = "true";
    int res = check_type(word);
    EXPECT_EQ(res, 3);
}

TEST(check_typeTest, ValidVoid)
{
    const std::string word = "null";
    int res = check_type(word);
    EXPECT_EQ(res, 4);
}

TEST(get_structTest, ValidInput)
{
    std::string inputt = "{\"key\" : \"value\"}";
    std::vector<std::string> struct_types = get_struct(inputt);
    EXPECT_THAT(struct_types, testing::ElementsAre("char* key"));
}

TEST(add_structTest, ValidInp)
{
    std::vector<std::string> struct_types = {"long 12"};
    std::string struct_name = "name";
    std::string res = add_struct(struct_types, struct_name);
    EXPECT_EQ(res, "name\n{\nlong 12;\n};");
}

TEST(dioTest, ValidInput)
{
    std::string inputt = "{\"key\" : \"value\"}";
    std::string struct_name = "StructName";
    std::string res = dio(inputt, struct_name);
    EXPECT_EQ(res, "StructName\n{\nchar* key;\n};");
}

TEST(CheckJsonTest, ValidInput)
{
    std::string input = "{\"key\" : \"value\"}";
    EXPECT_NO_THROW(check_json(input));
}

TEST(CheckJsonTest, InvalidInput1)
{
    std::string input = "{\"key\" : \"value\"";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput2)
{
    std::string input = "{\"key : \"value\"}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput3)
{
    std::string input = "{\"key\" \"value\"}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput4)
{
    std::string input = "{\"key\" : tru}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput5)
{
    std::string input = "{\"key : \"value\"}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput6)
{
    std::string input = "{key\" : \"value\"}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput7)
{
    std::string input = "\"key\" : \"value\"}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput8)
{
    std::string input = "{\"key : value}";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput9)
{
    std::string input = "{\"key\" : \"value\",";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput10)
{
    std::string invalidJson = "{\"key\":\"value}";
    EXPECT_THROW(check_json(invalidJson), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput11)
{
    std::string invalidJson = "{\"\":\"value}";
    EXPECT_THROW(check_json(invalidJson), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidSeparator)
{
    std::string invalidJson = "{\"key1\":\"value1\" \"key2\":123}";
    EXPECT_THROW(check_json(invalidJson), std::invalid_argument);
}

TEST(CheckJsonTest, ValidInputChar)
{
    char *input = new char[18]{};
    strcpy(input, "{\"key\" : \"value\"}");
    EXPECT_NO_THROW(check_json(input));
}

TEST(CheckJsonTest, InvalidInput1Char)
{
    char *input = new char[18]{};
    strcpy(input, "{\"key\" : \"value\"");
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, EmptyInput)
{
    char input[] = "";
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput2Char)
{
    char *input = new char[18]{};
    strcpy(input, "{\"key : \"value\"}");
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(CheckJsonTest, InvalidInput3Char)
{
    char *input = new char[18]{};
    strcpy(input, "{\"key\" \"value\"}");
    EXPECT_THROW(check_json(input), std::invalid_argument);
}

TEST(dioTest, ValidInputChar)
{
    char *inputt = new char[18]{};
    strcpy(inputt, "{\"key\" : \"value\"}");
    char *struct_name = new char[5]{};
    strcpy(struct_name, "Name");
    char *res = dio(inputt, struct_name);
    EXPECT_STREQ(res, "Name\n{\nchar* key;\n};");
    delete[] inputt;
    delete[] res;
    delete[] struct_name;
}

TEST(FreeStringsTest, ValidInputChar)
{
    int count = 2;
    char **arr = new char *[count] {};
    arr[0] = new char[10]{"Hello"};
    arr[1] = new char[10]{"world"};
    free_strings(arr, count);
    delete[] arr;
    SUCCEED();
}

TEST(WrongTypeException, CustomMessage)
{
    WrongTypeException e;
    EXPECT_EQ(e.get_message(), "Invalid type detected");
}

TEST(WrongTypeException, WhatMessage)
{
    WrongTypeException e;
    EXPECT_STREQ(e.what(), "Invalid type detected");
}

TEST(CheckJsonTest, ValidNumbers)
{
    std::string validJson = "{\"key\":123}";
    EXPECT_NO_THROW(check_json(validJson));
}

TEST(CheckJsonTest, ValidNegativeNumbers)
{
    std::string validJson = "{\"key\":-123}";
    EXPECT_NO_THROW(check_json(validJson));
}

TEST(CheckJsonTest, ValidFloatingNumbers)
{
    std::string validJson = "{\"key\":123.45}";
    EXPECT_NO_THROW(check_json(validJson));
}

TEST(TrimTest, OnlySpaces)
{
    std::string str = "     ";
    std::string expected = "";
    EXPECT_EQ(trim(str), expected);
}

TEST(CheckJsonTest, ValidJsonTrue)
{
    std::string validJson = "{\"key1\":true}";
    EXPECT_NO_THROW(check_json(validJson));
}

TEST(CheckJsonTest, ValidJsonFalse)
{
    std::string validJson = "{\"key1\":false}";
    EXPECT_NO_THROW(check_json(validJson));
}

TEST(CheckJsonTest, InvalidJsonInvalidBool)
{
    std::string invalidJson = "{\"key1\":invalid}";
    EXPECT_THROW(check_json(invalidJson), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}