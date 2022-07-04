//
// Created by ricardo on 2022/6/28.
//

#include "PosPair.h"

PosPair::PosPair()
{
    pos_x = stop_begin_x;
    pos_y = stop_begin_y;
}

int PosPair::GetStopSpaceLength(int stop_number)
{
    return 2 * (stop_rail_width + stop_rail_height) / stop_number;
}

void PosPair::AddLength(int length)
{
    distance += length;

    if(distance > 2 * stop_rail_width + stop_rail_height)
    {
        // 站点在左轨道

        pos_x = stop_begin_x;
        pos_y = stop_begin_y + (stop_rail_width + stop_rail_height) * 2 - distance;
    }
    else if(distance > stop_rail_width + stop_rail_height and
            distance <= 2 * stop_rail_width + stop_rail_height)
    {
        // 站点在下轨道

        pos_y = stop_begin_y + stop_rail_height;
        pos_x = stop_begin_x + 2 * stop_rail_width + stop_rail_height - distance;
    }
    else if(distance > stop_rail_width and
            distance <= stop_rail_width + stop_rail_height)
    {
        // 站点在右轨道

        pos_x = stop_begin_x + stop_rail_width;
        pos_y = stop_begin_y + distance - stop_rail_width;
    }
    else
    {
        // 站点在上轨道

        pos_y = stop_begin_y;
        pos_x = stop_begin_x + distance;
    }
}

int PosPair::GetBusPosX() const
{
    int result;

    if(pos_x <= stop_begin_x)
    {
        result = stop_begin_x - stop_bus_distance;
    }
    else if(pos_x >= stop_begin_x + stop_rail_width)
    {
        // 最右边一行得加上站点图片的宽度
        // 实际测试貌似不加就可以
        result = pos_x + stop_bus_distance;
    }
    else
    {
        result = pos_x;
    }

    return result;
}

int PosPair::GetBusPosY() const
{
    int result;

    if(pos_y <= stop_begin_y)
    {
        result = stop_begin_y - stop_bus_distance;
    }
    else if(pos_y >= stop_begin_y + stop_rail_height)
    {
        // 最下面一行得加上站点图片的高度
        result = pos_y + stop_bus_distance + 25;
    }
    else
    {
        result = pos_y;
    }

    return result;
}
