//
// Created by ricardo on 2022/6/10.
//

#include "railsModel.h"

RailsModel::RailsModel(int distance, int node_number)
{
    rail_node_t *head;
    rail_node_t *node;

    head = (rail_node_t *) malloc(sizeof(rail_node_t));
    head->id = 1;
    head->last_node_distance = distance;
    head->next_node_distance = distance;

    node = head;
    // 循环创建每一个节点
    for(int i = 2; i <= node_number; i++)
    {
        auto *p = (rail_node_t*) malloc(sizeof (rail_node_t));

        p->id = i;
        p->last_node_distance = distance;
        p->next_node_distance = distance;
        p->last_node = node;
        node->next_node = p;
        node = p;
    }

    // 将链表头尾链接起来
    node->next_node = head;
    head->last_node = node;

    rails = head;
}

RailsModel::~RailsModel()
{
    rail_node_t *node = rails;

    // 断开头尾节点
    node->last_node->next_node = nullptr;

    while (node != nullptr)
    {
        rail_node_t *p = node;
        node = node->next_node;
        free(p);
    }

    // 将指针置为空
    rails = nullptr;
}

rail_node_t *RailsModel::FindNode(int node_num) const
{
    if (rails == nullptr)
    {
        return nullptr;
    }

    rail_node_t *result = nullptr;
    rail_node_t *node = rails;

    do
    {
        if(node->id == node_num)
        {
            result = node;
            break;
        }
        node = node->next_node;
    } while (node != rails);

    return result;
}