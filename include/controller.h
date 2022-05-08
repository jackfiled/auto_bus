//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_CONTROLLER_H
#define AUTO_PILOT_BUS_CONTROLLER_H
#include "rail.h"
#include "query.h"

/**
 * 先来先服务的策略控制函数
 * @param rails 轨道链表
 * @param up_queries 上车请求队列
 * @param down_queries 下车请求队列
 * @return 车前进的方向
 */
int FCFSFunction(rail_node_t rails, up_bus_t up_queries, down_bus_t down_queries);

/**
 * 朢�短寻找时间优先的策略控制函数
 * @param rails 轨道链表
 * @param up_queries 上车请求队列
 * @param down_queries 下车请求队列
 * @return 车前进的方向
 */
int SSTFFunction(rail_node_t rails, up_bus_t up_queries, down_bus_t down_queries);

/**
 * 顺便服务的策略控制函敄1�7
 * @param rails 轨道链表
 * @param up_queries 上车请求队列
 * @param down_queries 下车请求队列
 * @return 车前进的方向
 */
int SCANFunction(rail_node_t rails, up_bus_t up_queries, down_bus_t down_queries);
int add(int a,int b);

#endif //AUTO_PILOT_BUS_CONTROLLER_H
