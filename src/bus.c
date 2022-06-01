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
    int a, b, c;
    b = 0;
    rail_node_t *p = rails;
    a = the_bus->rail_node_pos->id;//指向站点的指针以及这个指针对应的站台id
    if (a == 1 && (the_bus->distance < 0))
    {
        while(p->id != p->last_node->id)
        {
            b += p->next_node_distance;
            p = p->next_node;
        }
        b += p->next_node_distance;
        c = b + (the_bus->distance);
    }
    else
    {
        while (p->id != a){
            b += p->next_node_distance;
            p = p->next_node;
        }

        c = b + (the_bus->distance);
    }
    return c;
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