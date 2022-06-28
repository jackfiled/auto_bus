//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
#define AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
#include "BusStrategyBase.h"

class BusFCFSStrategy : public BusStrategyBase
{
    int GetBusDirection();

    bus_query_t *GetTargetQuery();

    bus_query_t *HandleQuery();
};


#endif //AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
