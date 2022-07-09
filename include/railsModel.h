//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_RAILS_MODEL_H
#define AUTO_BUS_GUI_RAILS_MODEL_H
#include "cstdlib"

/**
 * 站点结构体
 */
struct rail_node{
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

typedef struct rail_node rail_node_t;

/**
 * 轨道站点控制类
 */
class RailsModel
{

public:
    /**
     * 轨道的头节点
     */
    rail_node_t *rails;

    /**
     * 轨道上的节点数量
     */
    int node_num;

    /**
     * 轨道的总长度
     */
    int total_distance;

    explicit RailsModel();

    ~RailsModel();

    /**
     * 查找指定编号的站点指针
     * @param head 轨道的头节点地址
     * @param id 需要查找的站点编号
     * @return 需要查找站点指针
     */
    rail_node_t *FindNode(int node_id) const;

    /**
     * 创建轨道链表
     * @param distance 站点之间的距离
     * @param node_number 站点的数量
     */
    void CreateRails(int distance, int node_number);

    /**
     * 释放占用的内存空间
     */
    void FreeRails();

};

#endif //AUTO_BUS_GUI_RAILS_MODEL_H
