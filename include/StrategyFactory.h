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

/**
 * 策略控制对象工厂类
 */
class StrategyFactory
{
public:
    /**
     * 生成控制器的工厂函数
     * @param file_name 配置文件的名称
     * @return 控制器对象
     */
    static BusStrategyBase *GetStrategy(const QString& file_name);
};


#endif //AUTO_BUS_GUI_STRATEGY_FACTORY_H
