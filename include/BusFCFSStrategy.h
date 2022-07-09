//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
#define AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
#include "BusStrategyBase.h"

/**
 * 实现先来先服务策略的控制器类
 */
class BusFCFSStrategy : public BusStrategyBase
{
    int GetBusDirection() override;

    bus_query_t *GetTargetQuery() override;

    bus_query_t *HandleBTWQuery() override;
};


#endif //AUTO_BUS_GUI_BUS_FCFS_STRATEGY_H
