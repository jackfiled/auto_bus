//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_BUS_MODEL_H
#define AUTO_BUS_GUI_BUS_MODEL_H

#include "railsModel.h"
#include "queryModel.h"
#include "define.h"

#include "string"
#include "sstream"

class BusControllerModel
{
public:
    /**
     * 指向公交车所在站点的指针
     */
    rail_node_t *rail_pos;

    /**
     * 当前行进的距离
     */
    int distance;

    /**
     * 轨道对象
     */
    RailsModel *rail_manager;

    /**
     * 请求控制对象
     */
    QueryModel *query_manager;

    /**
     * 构造函数
     */
    BusControllerModel(RailsModel *railsModel, QueryModel *queryModel);

    /**
     * 析构函数
     */
    ~BusControllerModel();

    std::string PrintState();

private:
    int GetBusPosition() const;
};

#endif //AUTO_BUS_GUI_BUS_MODEL_H
