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
 * 全局的时间计数器
 */
extern int BUS_TIME;

/**
 * 当前正在处理的请求
 */
extern bus_query_t *target_query;

/**
 * 时间增加
 */
void AddTime();

/**
 * 在先来先服务策略下应该前进的方向
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 前进的方向
 */
int FCFSDirection(bus_t bus, bus_query_t queries);

/**
 * 在先来先服务策略下给出处理的请求
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 需要处理的请求
 */
bus_query_t FCFSQuery(bus_t bus, bus_query_t queries);

/**
 * 在最短寻找时间策略下应该前进的方向
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 前进的方向
 */
int SSTFDirection(bus_t bus, bus_query_t queries);

/**
 * 在最短寻找时间策略给出处理的请求
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 需要处理的请求
 */
bus_query_t SSTFQuery(bus_t bus, bus_query_t queries);

/**
 * 顺便服务的前进方向
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 前进的方向
 */
int SCANDirection(bus_t bus, bus_query_t queries);

/**
 * 顺便服务的策略处理
 * @param bus 公交车
 * @param queries 请求队列链表
 * @return 需要处理的请求
 */
bus_query_t SCANQuery(bus_t bus, bus_query_t queries);
#endif //AUTO_PILOT_BUS_CONTROLLER_H
