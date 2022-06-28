//
// Created by ricardo on 2022/6/27.
//

#include "BusSCANStrategy.h"

int BusSCANStrategy::GetBusDirection()
{
    int orientation = bus_model->direction;
    bus_query_t *query = bus_model->target_query;

    if(query == NULL)
    {
        return BUS_STOP;
    }

    if(orientation == BUS_STOP)
    {
        int distance = bus_model->GetQueryDistance(query, BUS_CLOCK_WISE);
        if(distance > rails_model->total_distance / 2)
        {
            return BUS_COUNTER_CLOCK_WISE;
        }
        else
        {
            return BUS_CLOCK_WISE;
        }
    }
    else
    {
        int distance = bus_model->GetQueryDistance(query, orientation);
        if(distance > rails_model->total_distance / 2)
        {
            if(orientation == BUS_CLOCK_WISE)
            {
                return BUS_COUNTER_CLOCK_WISE;
            }
            else
            {
                return BUS_CLOCK_WISE;
            }
        }
        else
        {
            return orientation;
        }
    }
}

bus_query_t *BusSCANStrategy::GetTargetQuery()
{
    bus_query_t *queries = query_model->queries;
    int direction = bus_model->direction;

    // 当前没有请求
    if(queries == NULL)
    {
        return NULL;
    }

    if(direction == BUS_STOP)
    {
        // 在停止的状态下第一次开始选择方向
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
    else
    {
        // 在已经有方向的情况下处理方向
        int distance = 9999;
        bus_query_t *query = NULL;
        bus_query_t *p = queries;

        while (p != NULL)
        {
            int temp = bus_model->GetQueryDistance(p, direction);
            if(temp < distance)
            {
                query = p;
                distance = temp;
            }
            p = p->next_node;
        }

        return query;
    }
}

bus_query_t *BusSCANStrategy::HandleBTWQuery()
{
    //获取公交车当前所在站点
    rail_node_t *now_position = bus_model->rail_pos;

    bus_query_t *p = query_model->queries;

    while(p != NULL)
    {
        if(p->node == now_position)
        {
            if(p->time < bus_tick - 1)
            {
                return p;
            }
        }
        p = p->next_node;
    }//遍历请求链表，判断是否有可以顺便处理的请求

    return NULL;
}
