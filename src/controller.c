//
// Created by ricardo on 2022/5/6.
//
#include "controller.h"

bus_query_t *target_query = NULL;
int chosen_strategy = -1;

int FCFSDirection()
{
    bus_query_t *p = queries;
    int id = the_bus->rail_node_pos->id;   //获取当前站点的id
    
    
    while(p->node->id == p->next_node->node->id)   //如果下一个请求对应的站点与当前是同一个站点
    {
        p = p->next_node;
    }   //处理完所有连续相同站点请求

    if(p->next_node == NULL)
    {
        return BUS_STOP;
    }   //如果没有请求了，公交车停止

    else
    {
        int clockwise = 0;
        int counterclockwise = 0;   //用于顺，逆时针方向所经站台计数
        bus_query_t *t = p;         //将指针p的地址暂存
    
        while(p->node->id != p->next_node->node->id)
        {
            p->node = p->node->next_node;
            clockwise++;
        }//顺时针方向计数
        while(t->node->id != t->next_node->node->id)
        {
            t->next_node->node = t->next_node->node->next_node;
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
