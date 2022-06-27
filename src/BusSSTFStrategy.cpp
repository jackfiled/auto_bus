//
// Created by ricardo on 2022/6/27.
//

#include "BusSSTFStrategy.h"

int BusSSTFStrategy::GetBusDirection(bus_query_t *query)
{
    if (query == NULL)
    {
        return BUS_STOP;
    }

    int distance = bus_model->GetQueryDistance(query, BUS_CLOCK_WISE);
    if(distance > rails_model->total_distance / 2)
    {
        return BUS_COUNTER_CLOCK_WISE;
    }
    else if(distance == 0)
    {
        return BUS_STOP;
    }
    else
    {
        return BUS_CLOCK_WISE;
    }
}

bus_query_t *BusSSTFStrategy::HandleQuery()
{
    // 这里只是处理顺便服务的代码

    bus_query_t *query = query_model->queries;
    bus_query_t *allow_query = NULL;
    rail_node_t *now_node = bus_model->rail_pos;

    while (query != NULL)
    {
        if(query->node == now_node)
        {
            // 这里是设计上的缺陷，在bus_time显示时间的前一秒，公交车就实际上到达站台了
            if(query->time < bus_tick - 1)
            {
                if(query->type == bus_model->direction || query->type == BUS_TARGET)
                {
                    allow_query = query;
                    break;
                }
            }
        }
        query = query->next_node;
    }

    return allow_query;
}

bus_query_t *BusSSTFStrategy::GetTargetQuery()
{
    // 获得请求头节点
    bus_query_t *queries = query_model->queries;

    // 当前没有请求
    if(queries == NULL)
    {
        return NULL;
    }

    int distance = 9999;
    bus_query_t *query = NULL;
    bus_query_t *p = queries;

    // 遍历顺时针方向
    // 在两个方向路程相同时选择顺时针方向
    // 所以先遍历顺时针方向
    while (p != NULL)
    {
        int temp = bus_model->GetQueryDistance(p, BUS_CLOCK_WISE);
        if(temp < distance)
        {
            distance = temp;
            query = p;
        }
        p = p->next_node;
    }

    // 遍历逆时针方向
    p = queries;
    while (p != NULL)
    {
        int temp = bus_model->GetQueryDistance(p, BUS_COUNTER_CLOCK_WISE);
        if(temp < distance)
        {
            distance = temp;
            query = p;
        }
        p = p->next_node;
    }

    return query;
}
