//
// Created by ricardo on 2022/6/27.
//

#include "BusFCFSStrategy.h"

int BusFCFSStrategy::GetBusDirection()
{
    bus_query_t *p = bus_model->target_query;

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
        rail_node_t *now_position = bus_model->rail_pos;
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

bus_query_t *BusFCFSStrategy::GetTargetQuery()
{
    return query_model->queries;
}

bus_query_t *BusFCFSStrategy::HandleQuery()
{
    bus_query_t *result = NULL;
    bus_query_t *query = query_model->queries;

    if(query != nullptr)
    {
        if(bus_model->rail_pos == query->node)
        {
            result = query;
        }
    }

    return result;
}
