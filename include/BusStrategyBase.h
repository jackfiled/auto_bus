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

    int bus_tick;
    int strategy;

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
     * 获取公交车现在可以顺便处理的请求
     * @return 请求指针
     */
    virtual bus_query_t *HandleBTWQuery() = 0;

    signals:
    /**
     * 删除请求信号
     * @param query 需要删除请求的指针
     */
    void DeleteQuerySignal(int query_type, int node_id);

    /**
     * 打印状态信号
     * @param string 状态字符串
     */
    void PrintStateSignal(QString string);

    /**
     * 获得公交车前进方向的信号
     */
    void GetBusDirectionSignal();

    /**
     * 运行公交车的信号
     * @param direction 公交车前进的方向
     * @param duration 前进需要的时间
     */
    void BusRunningSignal(int direction, int duration);

public slots:
    /**
     * 添加请求的槽函数
     * @param query_type 请求的类别
     * @param node_id 请求的站点ID
     */
    void AppendQuerySlot(int query_type, int node_id);

    /**
     * 处理开始事件的槽函数
     */
    void BusBeginSlot();

    /**
     * 处理结束事件的槽函数
     */
    void BusEndSlot();

    /**
     * 处理tick事件的槽函数
     */
    void OneTickSlot(int remaining_time);

    void GetBusDirectionSlot();

    void OnStopSlot();

private:
    /**
     * 储存当前的状态
     */
    int status = BUS_END;

    /**
     * 打印当前状态
     * @return 表示当前状态的字符串
     */
    QString PrintState(int remaining_time) const;


    void SetConnection() const;

    void HandleQuery();
};


#endif //AUTO_BUS_GUI_BUS_CONTROLLER_BASE_H
