//
// Created by ricardo on 2022/5/6.
//
#include "query.h"

bus_query_t *queries = NULL;

bus_query_t *CreateQuery(int type, rail_node_t *node)
{
    bus_query_t *p = (bus_query_t *)malloc(sizeof (bus_query_t));
    p->node = node;
    p->type = type;
    p->time = bus_time;
    p->next_node = NULL;

    if(queries == NULL)
    {
        queries = p;
    }
    else
    {
        // 寻找链表的末节点
        bus_query_t *last_node = queries;

        while(last_node->next_node != NULL)
        {
            last_node = last_node->next_node;
        }

        last_node->next_node = p;
    }

    return p;
}

void DeleteQuery(bus_query_t *target)
{
    if(target == queries)
    {
        queries = target->next_node;
    }
    else
    {
        bus_query_t *node = queries;

        // 找到被删除节点的上一个节点
        while(node->next_node != target)
        {
            node = node->next_node;
        }

        node->next_node = target->next_node;
    }

    free(target);
}

void FreeQueries(bus_query_t *head)
{
    bus_query_t *p = head;

    while (p != NULL)
    {
        bus_query_t *temp = p;
        p = p->next_node;
        free(temp);
    }

    // 将全局的请求列表头指针置为空
    queries = NULL;
}

