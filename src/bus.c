#include "bus.h"

bus_t *the_bus = NULL;

void RunBus(int direction)
{
    if(direction == BUS_CLOCK_WISE)//顺时针
    {
        the_bus->distance++;
    }
    else if(direction == BUS_COUNTER_CLOCK_WISE)
    {
        the_bus->distance--;
    }
}

int GetBusPosition()
{
    int distance = 0;
    rail_node_t *now_pos = the_bus->rail_node_pos;
    rail_node_t *p = rails;

    // 先计算当前所在站点距离起始站点的距离
    distance += p ->next_node_distance;
    p = p->next_node;
    while (p != now_pos)
    {
        distance += p->next_node_distance;
        p = p->next_node;
    }

    if(now_pos == rails) // 起始点特殊处理
    {
        // 公交车偏离起始点的位置
        int length = the_bus->distance;
        if(length >= 0)
        {
            return length;
        }
        else
        {
            return distance + length;
        }
    }
    else if(now_pos == rails->last_node)
    {
        int length = the_bus->distance;
        if(length == now_pos->next_node_distance) // 处理一种极为特殊的情况 公交车在即将到达起始站时
        {
            return 0;
        }
        else
        {
            return distance + length;
        }
    }
    else
    {
        return distance + the_bus->distance;
    }
}

int JudgeOnStation()
{
    if (the_bus->distance == - the_bus->rail_node_pos->last_node_distance)//表示逆时针
    {
        the_bus->distance = 0;
        the_bus->rail_node_pos = the_bus->rail_node_pos->last_node;//逆时针往上一个
        return BUS_TRUE;
    }
    else if (the_bus->distance == the_bus->rail_node_pos->next_node_distance)//表示顺时针
    {
        the_bus->distance = 0;
        the_bus->rail_node_pos = the_bus->rail_node_pos->next_node;//顺时针往下一个
        return BUS_TRUE;
    }
    else if(the_bus->distance == 0) //在站点上原地不动
    {
        return BUS_TRUE;
    }
    else
    {
        return BUS_FAlSE;
    }
}