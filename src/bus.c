#include "bus.h"
#include "math.h"
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
    int a,b;
    a=the_bus->rail_node_pos->id;//指向站点的指针以及这个指针对应的站台id；
    b=a*(rails->last_node_distance)+abs(the_bus->distance);
    return b;
}
int JudgeOnStation()
{
    if(abs(the_bus->distance) == rails->last_node_distance)//表示逆时针
    {
        the_bus->distance=0;
        the_bus->rail_node_pos=rails->last_node;//逆时针往上一个
        return BUS_TRUE;
    }
    else if(abs(the_bus->distance) == rails->next_node_distance)//表示顺时针
    {
        the_bus->distance=0;
        the_bus->rail_node_pos=rails->next_node;//顺时针往下一个
        return BUS_TRUE;
    }
    else
    {
        return BUS_FAlSE;
    }
}