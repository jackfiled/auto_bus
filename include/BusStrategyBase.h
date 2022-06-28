//
// Created by ricardo on 2022/6/27.
//

#ifndef AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
#define AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
#include "QObject"
#include "QString"
#include "QTimer"

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
    QTimer *tick_timer;


    int bus_tick;

    BusStrategyBase();

    virtual ~BusStrategyBase();

    /**
     * 获得当前公交车应该前进的方向
     * @return 公交车前进的方向
     */
    virtual int GetBusDirection() = 0;

    /**
     * 获得公交车在当前指定的策略下应该处理的请求
     * @return 请求指针
     */
    virtual bus_query_t *GetTargetQuery() = 0;

    /**
     * 获取公交车现在可以处理的请求
     * @return 请求指针
     */
    virtual bus_query_t *HandleQuery() = 0;

    signals:
    void DeleteQuerySignal(bus_query_t *query);

public slots:
    void AppendQuerySlot(int query_type, int node_id) const;


private:
    QString PrintState() const;

};


#endif //AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
