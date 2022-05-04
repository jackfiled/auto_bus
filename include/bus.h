#ifndef AUTO_PILOT_BUS_BUS_H
#define AUTO_PILOT_BUS_BUS_H

#include "rail.h"

struct {
    /**
     * 指向站点的指针
     */
    rail_node_t* rail_node_pos;
    /**
     * 当前行进的距离
     */
    int distance;
} bus;

/**
 * 表示公交车的结构体
 */
typedef struct bus bus_t;

#endif //AUTO_PILOT_BUS_BUS_H
