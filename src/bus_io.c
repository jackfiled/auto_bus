//
// Created by ricardo on 2022/5/6.
//
#include "bus_io.h"

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
        CreateQuery(BUS_COUNTER_CLOCK_WISE, FindNode(rails ,num));
        return IO_READING;
    }
    else if (0 == strcmp("clockwise",src))
    {
        CreateQuery(BUS_CLOCK_WISE,FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("target",src))
    {
        CreateQuery(BUS_TARGET,FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("end",src))
    {
        return IO_END;
    }
    else
    {
        // 匹配失败则返回-1
        return -1;
    }
    
}
