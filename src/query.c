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

    if (queries == NULL)
    {
        // 如果头指针是空指针，便没有必要排查是否重复
        queries = p;
        return p;
    }
    else
    {
        bus_query_t *query = queries;
        int flag = BUS_FAlSE;

        // 排查是否有重复的请求
        while (query != NULL)
        {
            if(query->node == p->node && query->type == p->type)
            {
                flag = BUS_TRUE;
                break;
            }
            query = query->next_node;
        }

        if(flag == BUS_TRUE)
        {
            // 如果存在相同的请求，这个请求就被放弃
            free(p);
            return NULL;
        }
        else
        {
            // 找到请求链表的最后一个节点
            bus_query_t *last_query = queries;

            while (last_query->next_node != NULL)
            {
                last_query = last_query->next_node;
            }

            last_query->next_node = p;
            return p;
        }
    }
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

