//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
#define AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
#include "QObject"
#include "QString"

#include "railsModel.h"
#include "queryModel.h"
#include "busModel.h"

class BusStrategyBase : public QObject
{
    Q_OBJECT
public:
    RailsModel *rails_model;
    QueryModel *query_model;
    BusModel *bus_model;

    int bus_tick;

    BusStrategyBase();

    virtual ~BusStrategyBase();

    virtual int GetBusDirection(bus_query_t *query) = 0;

    virtual bus_query_t *GetTargetQuery() = 0;

    virtual bus_query_t *HandleQuery() = 0;

private:
    QString PrintState() const;

};


#endif //AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
