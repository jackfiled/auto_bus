//
// Created by ricardo on 2022/6/10.
//

#include "busModel.h"

BusControllerModel::BusControllerModel()
{
    rail_manager = new RailsModel;
    query_manager = new QueryModel;

    // 设置公交车的初始状态
    rail_pos = rail_manager->rails;
    distance = 0;
    direction = BUS_STOP;
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

bool BusControllerModel::JudgeOnStation()
{
    if(distance == - rail_pos->last_node_distance)//表示逆时针
    {
        distance = 0;
        rail_pos = rail_pos->last_node;//逆时针往上一个
        return true;
    }
    else if(distance == rail_pos->next_node_distance)//表示顺时针
    {
        distance = 0;
        rail_pos = rail_pos->next_node;//顺时针往下一个
        return true;
    }
    else if(distance  == 0)//在站点上原地不动
    {
        return true;
    }
    else
    {
        return false;
    }
}

int BusControllerModel::GetQueryDistance(bus_query_t *query, int orientation) const
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

void BusControllerModel::ReadConfigFile(const std::string& file_name)
{
    FILE *config_file = nullptr;

    char buffer[30];
    int total_station = 0;
    int node_space_length = 0;

    fopen_s(&config_file, file_name.c_str(), "r");

    // 循环读取文件的每一行
    while (fgets(buffer, sizeof buffer, config_file) != nullptr)
    {
        char first_char = buffer[0];
        char *p;

        switch (first_char)
        {
            case '#':
                // 如果读取到#什么都不做
                break;
            case 'T':
                // TOTAL_STATION
                p = buffer;

                // 把数字前面的所有字符全部干掉
                while (*p < '0' || *p > '9')
                {
                    p++;
                }

                // 讲道理，应该只有两位数，所以就这样处理了
                if (*(p + 1) == '\n' || *(p + 1) == '\0')
                {
                    total_station = *p - 48;
                }
                else
                {
                    total_station = (*p - 48) * 10 + *(p + 1) - 48;
                }

                break;
            case 'S':
                // STRATEGY
                p = buffer;

                // 将=前的字符全部略去
                while (*p != '=')
                {
                    p++;
                }
                // =也去掉
                p++;
                // =和策略之间的空格也去掉
                while (*p == ' ')
                {
                    p++;
                }

                if (*p == 'F' && *(p + 1) == 'C') //FCFS
                {
                    chosen_strategy = BUS_FCFS;
                }
                else if (*p == 'S' && *(p + 1) == 'S') //SSTF
                {
                    chosen_strategy = BUS_SSTF;
                }
                else if (*p == 'S' && *(p + 1) == 'C') //SCAN
                {
                    chosen_strategy = BUS_SCAN;
                }
                else
                {
                    // 读取失败
                    chosen_strategy = -1;
                }

                break;
            case 'D':
                // DISTANCE
                p = buffer;

                // 把数字前面的所有字符全部干掉
                while (*p < '0' || *p > '9')
                {
                    p++;
                }

                if (*(p + 1) == '\n' || *(p + 1) == '\0')
                {
                    node_space_length = *p - 48;
                }

                break;
            default:
                continue;
        }
    }

    // 处理参数去缺省值的情况
    if (node_space_length == 0)
    {
        node_space_length = 2;
    }
    if (total_station == 0)
    {
        total_station = 5;
    }
    if(chosen_strategy == -1)
    {
        chosen_strategy = BUS_FCFS;
    }

    // 得到轨道的总长度
    total_distance = node_space_length * total_station;
    // 重新生成轨道模型
    delete rail_manager;
    rail_manager = new RailsModel(node_space_length, total_station);
}
