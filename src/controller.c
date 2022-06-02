//
// Created by ricardo on 2022/5/6.
//
#include "controller.h"
#include "math.h"

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

        /**
         * 公交车当前所在位置
         */
        rail_node_t *now_position = the_bus->rail_node_pos;
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

bus_query_t *FCFSQuery()
{
    bus_query_t *result = NULL;

    if(queries != NULL)
    {
        if(the_bus->rail_node_pos == queries->node)
        {
            result = queries;
        }
    }

    return result;
}

bus_query_t *SSTFGetQuery()
{
    int a,b,length,min;
    a = the_bus->rail_node_pos->id;  //是当前公交车的位置，而不是站点位置，应该两者差别不大
    b = rails->last_node->id;//总的站点数
    if (1 <= a <= b/2)//判断当前站点的位置
    {
        if (abs(a+b-queries->node->id) < abs(a-queries->node->id) ) //因为是环形轨道，用id相减的方式来计算距离的话，相减的方法不同
        {
            min = abs(a+b-queries->node->id);
        }
        else
        {
            min = abs(a-queries->node->id);
        }
    }
    else if (b/2 < a <=b)
    {
        if (abs(queries->node->id+b-a) < abs(a-queries->node->id))
        {
            min = abs(queries->node->id+b-a);
        }
        else
        {
            min = abs(a-queries->node->id);
        }
    }
    //通过上诉把第一个请求的距离置为最小值min
    bus_query_t *p = queries->next_node;
    bus_query_t *result = queries;//如果第一个请求即最近的那一个，result=第一个请求
    while (p->time <= bus_time)//在当前的时间找到所有请求中最近的一个
    {
        if (1 <= a <= b/2)//对当前站点所在的位置进行分类讨论
        {
            if (abs(a+b-p->node->id) <= abs(a-p->node->id) ) 
            {
                if(min >= abs(a+b-p->node->id))
                {
                    min = abs(a+b-p->node->id);
                    result = p;//把最小距离所对应的请求指针传给result
                    p = p->next_node;
                }
            }
        }
        else if (b/2 < a <=b)
        {
            if (abs(p->node->id+b-a) <= abs(a-p->node->id))
            {
                if (min >= abs(p->node->id+b-a))
                {
                    min = abs(p->node->id+b-a);
                    result = p;
                    p = p->next_node;
                }
            }
        }
    }
    return result;//需不需要返回空指针的情况呢？
}

int SSTFDirection(bus_query_t* query)
{
    if (query != NULL)
    {
        if (query->type != BUS_TARGET )
        {
            return query->type;
        }
    }
    else
    {
    return BUS_STOP;
    }
}

bus_query_t *SSTFBTWQuery()
{
    return NULL;
}

bus_query_t *SCANGetQuery()
{
    return NULL;
}

int SCANDirection(bus_query_t *query)
{
    return BUS_STOP;
}

bus_query_t *SCANBTWQuery()
{
    return NULL;
}