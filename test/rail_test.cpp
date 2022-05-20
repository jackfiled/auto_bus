//
// Created by ricardo on 2022/5/17.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "rail.h"
#ifdef __cplusplus
}
#endif

using namespace testing;

TEST(rail, CreateRails)
{
    rail_node_t *head = CreateRails(10, 10);
    rail_node_t *p = head;

    for(int i = 1; i <= 10; i++)
    {
        EXPECT_EQ(p->id, i);
        EXPECT_EQ(p->next_node_distance, 10);
        EXPECT_EQ(p->last_node_distance, 10);
        p = p->next_node;
    }

    p = head->last_node;
    for(int i = 10; i >= 1; i--)
    {
        EXPECT_EQ(p->id, i);
        EXPECT_EQ(p->next_node_distance, 10);
        EXPECT_EQ(p->last_node_distance, 10);
        p = p->last_node;
    }
}

TEST(rail, FindNode)
{
    rail_node_t *head = CreateRails(10, 10);
    rail_node_t *p;

    p = FindNode(head, 3);
    EXPECT_EQ(p->id, 3);

    p = FindNode(head, 9);
    EXPECT_EQ(p->id, 9);
}





