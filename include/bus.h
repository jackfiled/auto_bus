#ifndef AUTO_PILOT_BUS_BUS_H
#define AUTO_PILOT_BUS_BUS_H

#include "define.h"
#include "rail.h"
#include "query.h"

struct bus {
    /**
     * 指向站点的指针
     */
    rail_node_t* rail_node_pos;
    /**
     * 当前行进的距离
     */
    int distance;
};

/**
 * 表示公交车的结构体
 */
typedef struct bus bus_t;

/**
 * 全局的公交车变量
 */
extern bus_t *the_bus;

/**
 * 每个时刻使公交车前进
 * @param direction 公交车前进的方向
 */
void RunBus(int direction);

/**
 * 判断公交车是否到站
 * @return BUS_TRUE为到站，BUS_FALSE为未到站
 */
int JudgeOnStation();

/**
 * 获得公交车当前所在的位置
 * @return 公交车当前所在的位置
 */
int GetBusPosition();

/**
 * 给出在指定的方向下，指定的请求于公交车当前位置的距离
 * @param query 指定的请求
 * @param orientation 指定的方向 BUS_CLOCK_WISE BUS_COUNTER_CLOCK_WISE
 * @return 距离
 */
int GetQueryDistance(bus_query_t *query, int orientation);
#endif //AUTO_PILOT_BUS_BUS_H
