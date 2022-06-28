//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_SSTF_STRATEGY_H
#define AUTO_BUS_GUI_BUS_SSTF_STRATEGY_H
#include "BusStrategyBase.h"

class BusSSTFStrategy : public BusStrategyBase
{
    int GetBusDirection();

    bus_query_t *GetTargetQuery();

    bus_query_t *HandleBTWQuery();
};


#endif //AUTO_BUS_GUI_BUS_SSTF_STRATEGY_H
