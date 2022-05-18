//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_CONTROLLER_H
#define AUTO_PILOT_BUS_CONTROLLER_H
#include "stdlib.h"

#include "rail.h"
#include "query.h"
#include "bus.h"

/**
 * 当前正在处理的请求
 */
extern bus_query_t *target_query;

/**
 * 在先来先服务策略下应该前进的方向
 * @return 前进的方向
 */
int FCFSDirection();

/**
 * 在先来先服务策略下给出处理的请求
 * @return 需要处理的请求
 */
bus_query_t FCFSQuery();
#endif //AUTO_PILOT_BUS_CONTROLLER_H
