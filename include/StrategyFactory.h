//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_STRATEGY_FACTORY_H
#define AUTO_BUS_GUI_STRATEGY_FACTORY_H
#include "cstdio"
#include "QByteArray"

#include "BusStrategyBase.h"
#include "BusFCFSStrategy.h"
#include "BusSSTFStrategy.h"
#include "BusSCANStrategy.h"

class StrategyFactory
{
public:
    static BusStrategyBase *GetStrategy(const QString& file_name);
};


#endif //AUTO_BUS_GUI_STRATEGY_FACTORY_H
