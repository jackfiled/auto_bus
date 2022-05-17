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
#ifdef __cplusplus
}
#endif

using namespace testing;

TEST(test, test)
{
    int result = add(1, 1);
    EXPECT_EQ(2, result);
}