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
    return NULL;
}