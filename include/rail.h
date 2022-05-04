#ifndef AUTO_PILOT_BUS_RAIL_H
#define AUTO_PILOT_BUS_RAIL_H

struct {
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
} rail_node;

/**
 * 表示轨道上的一个站点的结构体
 */
typedef struct rail_node rail_node_t;

#endif //AUTO_PILOT_BUS_RAIL_H
