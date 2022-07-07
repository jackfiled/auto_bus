//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_SCAN_STRATEGY_H
#define AUTO_BUS_GUI_BUS_SCAN_STRATEGY_H
#include "BusStrategyBase.h"


class BusSCANStrategy : public BusStrategyBase
{
    int GetBusDirection() override;

    bus_query_t *GetTargetQuery() override;

    bus_query_t *HandleBTWQuery() override;

};


#endif //AUTO_BUS_GUI_BUS_SCAN_STRATEGY_H