//
// Created by ricardo on 2022/6/10.
//
#include "queryModel.h"

QueryModel::~QueryModel()
{
    if(queries != nullptr)
    {
        bus_query_t *p = queries;

        while (p != nullptr)
        {
            bus_query_t *temp = p;
            p = p->next_node;
            free(temp);
        }

        queries = nullptr;
    }
}

void QueryModel::CreateQuery(int type, rail_node_t *node)
{
    auto *p = (bus_query_t *)malloc(sizeof (bus_query_t));
    p->node = node;
    p->type = type;
    p->next_node = nullptr;

    if (queries == nullptr)
    {
        queries = p;
    }
    else
    {
        bus_query_t *query = queries;
        /**
         * 标记是否存在相同的请求
         */
        bool flag = false;

        do
        {
            if(query->node == p->node and query->type == p->type)
            {
                flag = true;
                break;
            }
            query = query->next_node;
        } while (query != nullptr);

        if (flag)
        {
            // 存在相同的请求
            free(p);
        }
        else
        {
            // 在不存在相同的请求时
            bus_query_t *last_query = queries;

            while (last_query->next_node != nullptr)
            {
                last_query = last_query->next_node;
            }

            last_query->next_node = p;
        }
    }
}

void QueryModel::DeleteQuery(bus_query_t *target_query)
{
    if (target_query == queries)
    {
        queries = target_query->next_node;
    }
    else
    {
        bus_query_t *query = queries;

        // 找到被删除节点的上一个节点
        while (query->next_node != target_query)
        {
            query = query->next_node;
        }

        query->next_node = target_query->next_node;
    }

    free(target_query);
}
