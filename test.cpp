#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "json_obj.h"

TEST(splitTest, ValidInput)
{
    std::vector<std::string> tokens;
    std::string inputt = "{\"key\" : \"value\"}";
    int count = 0;
    tokens = split(inputt, count);
    EXPECT_EQ(count, 2);
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

TEST(check_typeTest, InvalidStr)
{
    const std::string word = "";
    int res = check_type(word);
    EXPECT_EQ(res, -1);
}

TEST(get_structTest, ValidInput)
{
    std::string inputt = "{\"key\" : \"value\"}";
    std::vector<std::string> struct_types;
    std::vector<std::string> names;
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, 1);
    EXPECT_THAT(struct_types, testing::ElementsAre("char* "));
    EXPECT_THAT(names, testing::ElementsAre("key"));
}

TEST(get_structTest, InvalidInput)
{
    std::string inputt = "{\"key\" : \"=\"";
    std::vector<std::string> struct_types;
    std::vector<std::string> names;
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, -1);
    EXPECT_TRUE(struct_types.empty());
    EXPECT_THAT(names, testing::ElementsAre("key"));
}

TEST(get_structTest, EmptyInput)
{
    std::string inputt = "";
    std::vector<std::string> struct_types;
    std::vector<std::string> names;
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(struct_types.empty());
    EXPECT_TRUE(names.empty());
}

TEST(get_structTest, ValidInputChar)
{
    char *inputt = new char[20];
    strcpy(inputt, "{\"key\" : 1");
    char **struct_types = new char *[1];
    char **names = new char *[1];
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, -1);
    EXPECT_STREQ(struct_types[0], "long ");
    EXPECT_STREQ(names[0], "key");
    delete[] struct_types[0];
    delete struct_types;
    delete[] names[0];
    delete names;
    delete[] inputt;
}

TEST(get_structTest, InvalidInputChar)
{
    char inputt[20] = "{\"key\" : \"=\"";
    char **struct_types = new char *[1];
    char **names = new char *[1];
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, -1);
    EXPECT_STREQ(struct_types[0], NULL);
    EXPECT_STREQ(names[0], "key");
    delete[] struct_types[0];
    delete struct_types;
    delete[] names[0];
    delete names;
}

TEST(get_structTest, EmptyInputChar)
{
    char *inputt = NULL;
    char **struct_types;
    char **names;
    int result = get_struct(inputt, struct_types, names);
    EXPECT_EQ(result, -1);
    EXPECT_TRUE(struct_types == NULL);
    EXPECT_TRUE(names == NULL);
}

TEST(add_structTest, ValidInp)
{
    std::string res;
    std::vector<std::string> struct_types = {"int"};
    std::vector<std::string> names = {"val"};
    std::string struct_name = "name";
    int count = 1;
    add_struct(res, struct_types, names, struct_name, count);
    EXPECT_EQ(res, "name\n{\nintval\n}");
    EXPECT_THAT(struct_types, testing::ElementsAre("int"));
    EXPECT_THAT(names, testing::ElementsAre("val"));
    EXPECT_THAT(count, 1);
}

TEST(add_structTest, ValidInpChar)
{
    char *res = new char[100]{};
    char **struct_types = new char *[1];
    struct_types[0] = new char[7]{};
    strcpy(struct_types[0], "char* ");
    char **names = new char *[1];
    names[0] = new char[4]{};
    strcpy(names[0], "val");
    char struct_name[5] = "name";
    int count = 1;
    add_struct(res, struct_types, names, struct_name, count);
    EXPECT_STREQ(res, "name\n{\nchar* val\n}");
    EXPECT_STREQ(struct_types[0], "char* ");
    EXPECT_STREQ(names[0], "val");
    EXPECT_EQ(count, 1);
    delete[] res;
    delete[] struct_types[0];
    delete[] names[0];
    delete[] struct_types;
    delete[] names;
}

TEST(dioTest, ValidInput)
{
    std::string inputt = "{\"key\" : \"value\"}";
    std::string res;
    std::string struct_name = "StructName";
    int result = dio(res, inputt, struct_name);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(res, "StructName\n{\nchar* key\n}");
}

TEST(dioTest, InvalidInput)
{
    std::string inputt = "";
    std::string res;
    std::string struct_name = "StructName";
    int result = dio(res, inputt, struct_name);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(res, "");
}

TEST(dioTest, ValidInputСhar)
{
    char inputt[20] = "{\"key\" : \"value\"}";
    char *res = new char[100]{};
    char struct_name[13] = "StructName";
    int result = dio(res, inputt, struct_name);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(res, "StructName\n{\nchar* key\n}");
    delete[] res;
}

TEST(dioTest, InvalidInputChar)
{
    char inputt[20] = "";
    char *res = new char[100]{};
    char struct_name[13] = "StructName";
    int result = dio(res, inputt, struct_name);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(res, "");
    delete[] res;
}
TEST(check_typeTest, ValidCharChar)
{
    char word[7] = "\"word\"";
    int res = check_type(word);
    EXPECT_EQ(res, 0);
}

TEST(check_typeTest, ValidLongChar)
{
    char word[4] = "123";
    int res = check_type(word);
    EXPECT_EQ(res, 1);
}

TEST(check_typeTest, ValidDoubleChar)
{
    char word[4] = "1.3";
    int res = check_type(word);
    EXPECT_EQ(res, 2);
}

TEST(check_typeTest, ValidBoolChar)
{
    char word[5] = "true";
    int res = check_type(word);
    EXPECT_EQ(res, 3);
}

TEST(check_typeTest, ValidVoidChar)
{
    char word[5] = "null";
    int res = check_type(word);
    EXPECT_EQ(res, 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}