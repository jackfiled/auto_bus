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
    return NULL;
}

int SSTFDirection(bus_query_t* query)
{
    return BUS_STOP;
}

bus_query_t *SSTFBTWQuery()
{
    return NULL;
}

bus_query_t *SCANGetQuery()
{
    return NULL;
}

int SCANDirection(bus_query_t *query)
{
    return BUS_STOP;
}

bus_query_t *SCANBTWQuery()
{
    return NULL;
}