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
#include "controller.h"
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

TEST(bus_file, all)
{
    rail_node_t *result = ReadConfigFile();
    // 先测试轨道的参数读取是否正确
    rail_node_t *p = result;

    ASSERT_TRUE(p != nullptr);
    for(int i = 1; i <= 12; i++)
    {
        EXPECT_EQ(p->id, i);
        EXPECT_EQ(p->next_node_distance, 5);
        EXPECT_EQ(p->last_node_distance, 5);
        p = p->next_node;
    }

    p = result->last_node;
    for(int i = 12; i >= 1; i--)
    {
        EXPECT_EQ(p->id, i);
        EXPECT_EQ(p->next_node_distance, 5);
        EXPECT_EQ(p->last_node_distance, 5);
        p = p->last_node;
    }

    EXPECT_EQ(chosen_strategy, BUS_FCFS);
}