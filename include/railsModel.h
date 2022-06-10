//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_RAILSMODEL_H
#define AUTO_BUS_GUI_RAILSMODEL_H
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

    explicit RailsModel(int distance = 2, int node_number = 5);
    rail_node_t *FindNode(int node_num) const;
    ~RailsModel();



};

#endif //AUTO_BUS_GUI_RAILSMODEL_H
