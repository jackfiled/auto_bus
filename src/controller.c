//
// Created by ricardo on 2022/5/6.
//
#include "controller.h"

bus_query_t *target_query = NULL;
int chosen_strategy = -1;

int FCFSDirection()
{
    return BUS_STOP;
}

bus_query_t *FCFSQuery()
{
    bus_query_t *p = queries;
    if (the_bus->rail_node_pos == p->node)
    {
        return p;
    }
    else
    { 
        queries = queries->next_node;
        return NULL;
    }
}