//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_BUS_MODEL_H
#define AUTO_BUS_GUI_BUS_MODEL_H

#include "railsModel.h"
#include "queryModel.h"
#include "define.h"

#include "QObject"
#include "QDebug"
#include "QTimer"

/**
 * 公交车模型类
 */
class BusModel
{
public:
    rail_node_t *rail_pos;

    /**
     * 公交车前进的速度
     */
    const int velocity = 1;

    /**
     * 当前前进的方向
     */
    int direction;

    /**
     * 当前指定处理的请求
     */
    bus_query_t *target_query;

    QTimer *bus_timer;

    explicit BusModel();

    ~BusModel();

    /**
     * 重置公交车
     * @param head 轨道的头节点位置
     */
    void ResetBus(rail_node_t *head);

    double GetBusPosition();

    /**
     * 给出在指定的方向下，指定的请求于公交车当前位置的距离
     * @param query 指定的请求
     * @param orientation 指定的方向 BUS_CLOCK_WISE BUS_COUNTER_CLOCK_WISE
     * @return 距离
     */
    int GetQueryDistance(bus_query_t *query, int orientation) const;

private:
    /**
     * 轨道的头节点
     */
    rail_node_t *rail_head;
};

#endif //AUTO_BUS_GUI_BUS_MODEL_H
