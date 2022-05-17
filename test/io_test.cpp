//
// Created by ricardo on 2022/5/7.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
// 在C++中引用C语言中的函数
#ifdef __cplusplus
extern "C"
{
#endif
#include "rail.h"
#include "bus_io.h"
#include "query.h"
#include "define.h"
#ifdef __cplusplus
}
#endif

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;

using namespace testing;

TEST(test, test)
{
    int result = add(1, 1);
    EXPECT_EQ(2, result);
}

/**
 * 测试输入读取函数读取clock时的行为
 */
TEST(io_test, io_clock)
{
    char input[7] = "clock\n";
    int result = ReadInput(input);
    EXPECT_EQ(result, IO_CLOCK);
}

/**
 * 测试顺时针3号站台上车请求
 */
TEST(io_test, reading)
{
    char input[] = "counterclockwise 3\n";
    int result = ReadInput(input);
    EXPECT_EQ(result, IO_READING);
}

TEST(io_test, end)
{
    char input[] = "end\n";
    int result = ReadInput(input);
    EXPECT_EQ(result, IO_END);
}