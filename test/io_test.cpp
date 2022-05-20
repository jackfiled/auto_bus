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
#include "bus_io.h"
#include "define.h"
#ifdef __cplusplus
}
#endif

using namespace testing;

TEST(bus_io, ReadInput_clock)
{
    int result;
    char str[10] = "clock\n";
    result = ReadInput(str);
    EXPECT_EQ(result, IO_CLOCK);
}

TEST(bus_io, ReadInput_end)
{
    char str[5] = "end\n";
    int result = ReadInput(str);
    EXPECT_EQ(result, IO_END);
}

TEST(bus_io, ReadInput_reading)
{
    char str[20] = "target 8\n";
    int result = ReadInput(str);
    EXPECT_EQ(result, IO_READING);
}