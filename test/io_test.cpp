//
// Created by ricardo on 2022/5/7.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
extern "C"
{
#include "rail.h"
}

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::Exactly;

using namespace testing;

TEST(test, test)
{
    int result = add(1, 1);
    EXPECT_EQ(2, result);
}
