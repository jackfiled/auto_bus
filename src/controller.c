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
    
        while(p->node != p->next_node->node)
        {
            p->node = p->node->next_node;
            clockwise++;
        }//顺时针方向计数
        while(p->node != p->next_node->node)
        {
            p->next_node->node = p->next_node->node->next_node;
            counterclockwise++;
        }//逆时针方向计数
        
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
    return NULL;
}

bus_query_t *SSTFGetQuery()
{
    return NULL;
}

int SSTFDirection(bus_query_t* target_query)
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

int SCANDirection(bus_query_t *target_query)
{
    return BUS_STOP;
}

bus_query_t *SCANBTWQuery()
{
    return NULL;
}