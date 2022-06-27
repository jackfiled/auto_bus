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

    bus_timer = new QTimer;
}

BusModel::~BusModel()
{
    delete bus_timer;
}

void BusModel::ResetBus(rail_node_t *head)
{
    rail_head = head;

    direction = BUS_STOP;
    target_query = nullptr;
    rail_pos = rail_head;
}

double BusModel::GetBusPosition()
{
    double result = 0;
    rail_node_t *now_pos = rail_pos;
    rail_node_t *node = rail_head;

    // 先求一下当前所在位置离起始点的距离
    do
    {
        result += node->next_node_distance;
        node = node->next_node;
    } while (node != now_pos);

    int remaining_time = bus_timer->remainingTime();

    if(remaining_time > 0)
    {
        if(direction == BUS_CLOCK_WISE)
        {
            double length = now_pos->next_node_distance - (double)remaining_time / 1000.0 * velocity;
            result = result + length;
        }
        else if(direction == BUS_COUNTER_CLOCK_WISE)
        {
            double length = now_pos->last_node_distance - (double)remaining_time / 1000.0 * velocity;
            result = result - length;
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
