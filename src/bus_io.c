//
// Created by ricardo on 2022/5/6.
//
#include "bus_io.h"
#include "define.h"

int ReadInput(char* inputString)
{
    
    char src[20];
    int num;
    sscanf(inputString,"%[a-z] %d",src,&num);
    if (0 == strcmp("clock",src))
    {
        return IO_CLOCK;
    }
    else if (0 == strcmp("counterclockwise",src))
    {
        bus_query_t *CreateQuery(BUS_COUNTER_CLOCK_WISE, FindNode(num));
        return IO_READING;
    }
    else if (0 == strcmp("clockwise",src))
    {
        bus_query_t *CreateQuery(BUS_CLOCK_WISE,FindNode(num));
        return IO_READING;
    }
    else if (0 == strcmp("target",src))
    {
        bus_query_t *CreateQuery(BUS_TARGET,FindNode(num));
        return IO_READING;
    }
    else if (0 == strcmp("end",src))
    {
        return IO_END;
    }
    
}
