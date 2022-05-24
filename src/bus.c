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
    if(abs(the_bus->distance) == rails->last_node_distance)
    {
        return BUS_TRUE;
    }
    else 
    {
        return BUS_FAlSE;
    }
}