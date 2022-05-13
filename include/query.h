//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_QUERY_H
#define AUTO_PILOT_BUS_QUERY_H
#include "stdlib.h"
#include "rail.h"

struct up_bus {
    /**
     * 请求的序号
     */
    int id;
    /**
     * 请求前往的方向
     */
    int direction;
    /**
     * 请求上车的地点
     */
    rail_node_t* target;
    struct up_bus* next;
};

struct down_bus {
    /**
     * 请求的序号
     */
    int id;
    /**
     * 请求下车的地点
     */
    rail_node_t* target;
    struct down_bus* next;
};

/**
 *  表示上车请求的结构体
 */
typedef struct up_bus up_bus_t;
/**
 * 表示下车请求的结构体
 */
typedef struct down_bus down_bus_t;

/**
 * 全局的上车请求链表头节点地址，也就是当前未处理的首个请求
 */
extern up_bus_t *up_queries;

/**
 * 全局的下车请求链表头节点地址，也就是当前未处理的首个请求
 */
extern down_bus_t *down_queries;

/**
 * 创建一个上车请求
 * @param target 上车的地点
 * @param direction 需要前往的方向
 */
void CreateUpBusQuery(rail_node_t* target, int direction);

/**
 * 删除一个上车请求
 * @param id 需要删除的请求编号
 */
void DeleteUpBusQuery(int id);

/**
 * 创建一个下车请求
 * @param target 需要下车的地点
 */
void CreateDownBusQuery(rail_node_t *target);

/**
 * 删除一个下车请求
 * @param id 需要删除的请求编号
 */
void DeleteDownBusQuery(int id);

#endif //AUTO_PILOT_BUS_QUERY_H
