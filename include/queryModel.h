//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_QUERYMODEL_H
#define AUTO_BUS_GUI_QUERYMODEL_H
#include "railsModel.h"

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

class QueryModel
{
public:
    bus_query_t *queries = nullptr;

    /**
     * 析构函数
     * 负责释放内存
     */
    ~QueryModel();

    /**
     * 创建请求节点
     * @param type 请求的链表
     * @param node 请求的节点
     */
    void CreateQuery(int type, rail_node_t *node);

    /**
     * 删除创建的请求节点
     * @param target_query 需要删除的节点
     */
    void DeleteQuery(bus_query_t *target_query);

};

#endif //AUTO_BUS_GUI_QUERYMODEL_H
