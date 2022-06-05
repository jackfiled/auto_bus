//
// Created by ricardo on 2022/5/6.
//
#include "controller.h"

bus_query_t *target_query = NULL;
int chosen_strategy = -1;

int FCFSDirection()
{
    bus_query_t *p = queries;
    
    if(p == NULL)
    {
        return BUS_STOP;
    }   //如果没有请求，公交车停止

    else
    {
        int clockwise = 0;
        int counterclockwise = 0;   //用于顺，逆时针方向所经站台计数

        /**
         * 公交车当前所在位置
         */
        rail_node_t *now_position = the_bus->rail_node_pos;
        /**
         * 公交车应该前进的方向
         */
        rail_node_t *target_position = p->node;

        rail_node_t *pos = now_position;
        while (pos != target_position) //顺时针计数
        {
            clockwise++;
            pos = pos->next_node;
        }

        pos = now_position;
        while (pos != target_position) //逆时针计数
        {
            counterclockwise++;
            pos = pos->last_node;
        }
        
        if(clockwise <= counterclockwise)
        {
            return BUS_CLOCK_WISE;
        }//若顺时针距离短(或顺逆相等)，公交车顺时针运行
        else
        {
            return BUS_COUNTER_CLOCK_WISE;
        }//若逆时针距离短，公交车逆时针运行
    }
}

bus_query_t *FCFSQuery()
{
    bus_query_t *result = NULL;

    if(queries != NULL)
    {
        if(the_bus->rail_node_pos == queries->node)
        {
            result = queries;
        }
    }

    return result;
}

bus_query_t *SSTFGetQuery()
{
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
        int temp = GetQueryDistance(p, BUS_CLOCK_WISE);
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
        int temp = GetQueryDistance(p, BUS_COUNTER_CLOCK_WISE);
        if(temp < distance)
        {
            distance = temp;
            query = p;
        }
        p = p->next_node;
    }

    return query;
}

int SSTFDirection(bus_query_t* query)
{
    if (query == NULL)
    {
        return BUS_STOP;
    }

    int distance = GetQueryDistance(query, BUS_CLOCK_WISE);
    if(distance > all_distance / 2)
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

bus_query_t *SSTFBTWQuery(int direction)
{
    bus_query_t *query = queries;
    bus_query_t *allow_query = NULL;
    rail_node_t *now_node = the_bus->rail_node_pos;

    while (query != NULL)
    {
        if(query->node == now_node)
        {
            // 这里是设计上的缺陷，在bus_time显示时间的前一秒，公交车就实际上到达站台了
            if(query->time < bus_time - 1)
            {
                if(query->type == direction || query->type == BUS_TARGET)
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

bus_query_t *SCANGetQuery(int direction)
{
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
            int temp = GetQueryDistance(p, BUS_CLOCK_WISE);
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
            int temp = GetQueryDistance(p, BUS_COUNTER_CLOCK_WISE);
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
            int temp = GetQueryDistance(p, direction);
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

int SCANDirection(bus_query_t *query, int orientation)
{
    if(query == NULL)
    {
        return BUS_STOP;
    }

    if(orientation == BUS_STOP)
    {
        int distance = GetQueryDistance(query, BUS_CLOCK_WISE);
        if(distance > all_distance / 2)
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
        int distance = GetQueryDistance(query, orientation);
        if(distance > all_distance / 2)
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

bus_query_t *SCANBTWQuery()
{
    rail_node_t *now_position = the_bus->rail_node_pos;
    //获取公交车当前所在站点
    bus_query_t *p = queries;
    
    while(p != NULL)
    {
        if(p->node == now_position)
        {
            if(p->time < bus_time - 1)
            {
                return p;
            }
        }
        p = p->next_node;
    }//遍历请求链表，判断是否有可以顺便处理的请求

    return NULL;
}