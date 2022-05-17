//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_QUERY_H
#define AUTO_PILOT_BUS_QUERY_H
#include "stdlib.h"
#include "rail.h"

struct bus_query {
    /**
     * 请求产生的时间
     */
    int time;
    /**
     * 请求的类型
     */
    int type;
    /**
     * 请求产生/指向的站点
     */
    rail_node_t node;
};

typedef struct bus_query bus_query_t;

/**
 * 创建请求
 * @param query 请求链表队列
 * @param type 请求的类型
 * @param node 请求产生/指向的站点
 */
void CreateQuery(bus_query_t query, int type, rail_node_t node);

/**
 * 删除请求
 * @param query 请求链表队列
 * @param target_query 需要删除的请求
 */
void DeleteQuery(bus_query_t query, bus_query_t target_query);

/**
 * 释放请求链表占据的空间
 * @param queries 请求链表的头节点
 */
void FreeQueries(bus_query_t queries);

#endif //AUTO_PILOT_BUS_QUERY_H
