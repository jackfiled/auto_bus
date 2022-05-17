#ifndef AUTO_PILOT_BUS_RAIL_H
#define AUTO_PILOT_BUS_RAIL_H
#include "stdlib.h"

struct rail_node {
    /**
     * 站点的编号
     */
    int id;
    /**
     * 距离上一个站点的距离
     */
    int last_node_distance;
    /**
     * 距离下一个站点的距离
     */
    int next_node_distance;
    /**
     * 指向上一个站点的指针
     */
    struct rail_node* last_node;
    /**
     * 指向下一个站点的指针
     */
    struct rail_node* next_node;
};

/**
 * 表示轨道上的一个站点的结构体
 */
typedef struct rail_node rail_node_t;

/**
 * 全局的轨道链表头节点，也就是第一个公交站
 */
extern rail_node_t *rails;

/**
 * 查找指定编号的站点指针
 * @param rails 轨道的头节点地址
 * @param id 需要查找的站点编号
 * @return 需要查找站点指针
 */
rail_node_t *FindNode(rail_node_t rails, int id);

/**
 * 创建轨道列表
 * @param length 站点之间的距离
 * @param node_num 站点的个数
 * @return 指向首站的指针
 */
rail_node_t *CreateRails(int length, int node_num);

/**
 * 释放分配的内存空间
 * @param railNode 轨道链表的头节点
 */
void FreeRails(rail_node_t railNode);

int add(int a, int b);

#endif //AUTO_PILOT_BUS_RAIL_H
