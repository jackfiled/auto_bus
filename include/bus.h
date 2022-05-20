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
 * @param rails 轨道链表
 * @param direction 公交车前进的方向
 * @param bus 公交车
 * @return 公交车是否到达站点
 */
int RunBus(int direction);

#endif //AUTO_PILOT_BUS_BUS_H
