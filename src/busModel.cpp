//
// Created by ricardo on 2022/6/10.
//

#include "busModel.h"

BusControllerModel::BusControllerModel(RailsModel *railsModel, QueryModel *queryModel)
{
    rail_manager = railsModel;
    query_manager = queryModel;

    // 公交车开始时停在轨道起始处
    rail_pos = railsModel->rails;
    distance = 0;
}

BusControllerModel::~BusControllerModel()
{
    delete(rail_manager);
    delete(query_manager);
}

int BusControllerModel::GetBusPosition() const
{
    int result = 0;
    rail_node_t *now_pos = rail_pos;
    rail_node_t *node = rail_manager->rails;

    // 先求一下当前所在位置离起始点的距离
    do
    {
        result += node->next_node_distance;
        node = node->next_node;
    } while (node != now_pos);

    if (now_pos == rail_manager->rails)
    {
        int length = distance;
        if(length >= 0)
        {
            return length;
        }
        else
        {
            return result + length;
        }
    }
    else if (now_pos == rail_manager->rails->last_node)
    {
        int length = distance;
        if (length == now_pos->next_node_distance)
        {
            return 0;
        }
        else
        {
            return distance + length;
        }
    }
    else
    {
        return result + distance;
    }
}

std::string BusControllerModel::PrintState()
{
    int count, flag = 1;
    rail_node_t *node;
    char target[25], clockwise[25], counterclockwise[25];

    //遍历轨道链表，将所有站点初始化为0，即：无任何请求；
    for (count = 0, node = rail_manager->rails; flag == 1 || node != rail_manager->rails;
        node = node->next_node, count++)
    {
        flag=0;
        target[count] = '0';
        clockwise[count] = '0';
        counterclockwise[count] = '0';
    }

    // 在字符串的末尾填0
    target[count] = '\0';
    clockwise[count] = '\0';
    counterclockwise[count] = '\0';

    bus_query_t *query = query_manager->queries;
    int pos;

    while (query != nullptr)
    {
        pos = query->node->id - 1;

        if(query->type == BUS_CLOCK_WISE)
        {
            clockwise[pos] = '1';
        }
        else if (query->type == BUS_COUNTER_CLOCK_WISE)
        {
            counterclockwise[pos] = '1';
        }
        else
        {
            target[pos] = '1';
        }

        query = query->next_node;
    }

    std::stringstream format;

    // 格式化输出字符串
    format << "Time:" << std::endl
           << "BUS:" << std::endl
           << "position:" << GetBusPosition() << std::endl
           << "target:" << target << std::endl
           << "STATION:" << std::endl
           << "clockwise:" << clockwise << std::endl
           << "counterclockwise:" << counterclockwise << std::endl;

    return format.str();
}
