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
 * 当前选择的策略
 */
extern int chosen_strategy;

/**
 * 在先来先服务策略下应该前进的方向
 * @return 前进的方向
 */
int FCFSDirection();

/**
 * 在先来先服务策略下给出处理的请求
 * @return 需要处理的请求
 */
bus_query_t *FCFSQuery();

/**
 * 获得在SSTF策略下应该处理的请求
 * @return 指向需要处理的请求的指针
 */
bus_query_t *SSTFGetQuery();

/**
 * 根据指定的请求获得前进的方向，也就是前往指定的请求最近的方向
 * 在SSTF策略中使用
 * @param target_query 指定完成的请求
 * @return 前进的方向
 */
int SSTFDirection(bus_query_t* target_query);

/**
 * 在当前站上可以顺便服务的请求
 * @return 服务的请求指针
 */
bus_query_t *SSTFBTWQuery();

/**
 * 获得在SCAN策略下应该处理的请求
 * @return 指向需要处理的请求的指针
 */
bus_query_t *SCANGetQuery();

/**
 * 根据指定的请求获得前进的方向
 * 在SCAN策略中使用
 * @param target_query 指定完成的请求
 * @return 前进的方向
 */
int SCANDirection(bus_query_t *target_query);

/**
 * 在当前站上可以顺便服务的请求
 * @return 服务的请求指针
 */
bus_query_t *SCANBTWQuery();
#endif //AUTO_PILOT_BUS_CONTROLLER_H
