//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_RAILS_MODEL_H
#define AUTO_BUS_GUI_RAILS_MODEL_H
#include "cstdlib"

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

class RailsModel
{

public:
    /**
     * 轨道的头节点
     */
    rail_node_t *rails;

    /**
     * 生成相关的轨道对象
     * @param distance 站点直接的距离
     * @param node_number 站点的数量
     */
    explicit RailsModel(int distance = 2, int node_number = 5);
    /**
     * 查找指定编号的站点指针
     * @param head 轨道的头节点地址
     * @param id 需要查找的站点编号
     * @return 需要查找站点指针
     */
    rail_node_t *FindNode(int node_num) const;
    ~RailsModel();



};

#endif //AUTO_BUS_GUI_RAILS_MODEL_H
