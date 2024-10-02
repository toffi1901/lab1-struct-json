#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "json_obj.h"

TEST(splitTest, ValidInput)
{
    std::vector<std::string> tokens;
    std::string inputt = "{\"key\" : \"value\"}";
    tokens = split(inputt);
    EXPECT_THAT(tokens, testing::ElementsAre("\"key\"", "\"value\""));
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
    std::vector<std::string> struct_types;
    get_struct(inputt, struct_types);
    EXPECT_THAT(struct_types, testing::ElementsAre("char* key"));
}

TEST(add_structTest, ValidInp)
{
    std::string res;
    std::vector<std::string> struct_types = {"long 12"};
    std::string struct_name = "name";
    add_struct(res, struct_types, struct_name);
    EXPECT_EQ(res, "name\n{\nlong 12\n}");
}

TEST(dioTest, ValidInput)
{
    std::string inputt = "{\"key\" : \"value\"}";
    std::string res;
    std::string struct_name = "StructName";
    dio(res, inputt, struct_name);
    EXPECT_EQ(res, "StructName\n{\nchar* key\n}");
}

TEST(dioTest, ValidInputСhar)
{
    char *inputt = new char[18]{};
    strcpy(inputt, "{\"key\" : \"value\"}");
    char *res = NULL;
    char *struct_name = new char[5]{};
    strcpy(struct_name, "Name");
    dio(res, inputt, struct_name);
    EXPECT_STREQ(res, "Name\n{\nchar* key\n}");
    delete[] inputt;
    delete[] res;
    delete[] struct_name;
}

TEST(EmptynessTest, InvalidInput)
{
    std::string input = "";
    EXPECT_THROW(EmptyStrInput(input), std::invalid_argument);
}

TEST(EmptynessTest, ValidInput)
{
    std::string input = "Hello, world!";
    EXPECT_NO_THROW(EmptyStrInput(input));
}

TEST(CheckJsonTest, ValidInput)
{
    std::string input = "{\"key\" : \"value\"}";
    EXPECT_NO_THROW(check_json(input));
}

TEST(CheckJsonTest, InvalidInput1)
{
    std::string input = "{key\" : \"value\"";
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}