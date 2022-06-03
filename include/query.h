//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_QUERY_H
#define AUTO_PILOT_BUS_QUERY_H
#include "stdlib.h"
#include "rail.h"
#include "define.h"

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
    rail_node_t *node;
    /**
     * 指向下一个请求的指针
     */
    struct bus_query *next_node;
};

typedef struct bus_query bus_query_t;

/**
 * 全局的请求链表头节点
 */
extern bus_query_t *queries;

/**
 * 创建请求链表节点
 * @param type 请求的类型
 * @param node 请求产生/指向的站点
 * @return 当前创建的链表节点地址
 */
bus_query_t *CreateQuery(int type, rail_node_t *node);

/**
 * 删除请求
 * @param target_query 需要删除的请求
 */
void DeleteQuery(bus_query_t *target_query);

/**
 * 释放请求链表占据的空间
 * @param head 请求链表的头节点
 */
void FreeQueries(bus_query_t *head);

#endif //AUTO_PILOT_BUS_QUERY_H
