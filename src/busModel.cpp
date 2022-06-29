//
// Created by ricardo on 2022/6/10.
//

#include "busModel.h"

BusModel::BusModel()
{
    rail_pos = nullptr;
    direction = BUS_STOP;
    target_query = nullptr;
    rail_head = nullptr;
}

BusModel::~BusModel()
{

}

void BusModel::ResetBus(rail_node_t *head)
{
    rail_head = head;

    direction = BUS_STOP;
    target_query = nullptr;
    rail_pos = rail_head;
}

double BusModel::GetBusPosition(int remaining_time)
{
    double result = 0;
    double length = 0;
    rail_node_t *now_pos = rail_pos;
    rail_node_t *node = rail_head;

    // 先求一下当前所在位置离起始点的距离
    do
    {
        result += node->next_node_distance;
        node = node->next_node;
    } while (node != now_pos);

    // 获得可能存在的偏移量
    if(remaining_time > 0)
    {
        if(direction == BUS_CLOCK_WISE)
        {
            length = now_pos->next_node_distance - (double)remaining_time / 1000.0 * velocity;
        }
        else if(direction == BUS_COUNTER_CLOCK_WISE)
        {
            length = now_pos->last_node_distance - (double)remaining_time / 1000.0 * velocity;
            length = -length;
        }
    }

    if(now_pos == rail_head)
    {
        // 在起点
        if(length >= 0)
        {
            result = length;
        }
        else
        {
            result = result + length;
        }
    }
    else
    {
        // 在其他点
        if(now_pos == rail_head->last_node and length == -rail_head->last_node_distance)
        {
            // 恰好即将回到出发点的情况
            result = 0;
        }
        else
        {
            result = result + length;
        }
    }

    return result;
}


int BusModel::GetQueryDistance(bus_query_t *query, int orientation) const
{
    rail_node_t *target_node = query->node;
    rail_node_t *now_node = rail_pos;
    int result = 0;

    if(orientation == BUS_CLOCK_WISE)
    {
        while (now_node != target_node)
        {
            result += now_node->next_node_distance;
            now_node = now_node->next_node;
        }
    }
    else if(orientation == BUS_COUNTER_CLOCK_WISE)
    {
        while (now_node != target_node)
        {
            result += now_node->last_node_distance;
            now_node = now_node->last_node;
        }
    }

    return result;
}
