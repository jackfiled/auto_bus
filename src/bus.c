#include "bus.h"
#include "math.h"
bus_t *the_bus = NULL;
void RunBus(int direction)
{
    if(direction == 0)//顺时针
    {
        the_bus->distance++;
        if(the_bus->distance == rails->next_node_distance)
        {
            the_bus->distance=0;//到达一个站点用重新置为0
        }
    }
    else if(direction == 1)
    {
        the_bus->distance--;
        if(abs(the_bus->distance) ==rails->last_node_distance)
        {
            the_bus->distance=0;//到达一个站点又重新置为0
        }
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
        return 1;
    }
    else 
    {
        return 0;
    }
}