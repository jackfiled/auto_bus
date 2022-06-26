//
// Created by ricardo on 2022/6/10.
//

#include "moc_busModel.cpp"

BusControllerModel::BusControllerModel()
{
    rail_manager = new RailsModel;
    query_manager = new QueryModel;

    // 设置公交车的初始状态
    rail_pos = rail_manager->rails;
    distance = 0;
    direction = BUS_STOP;

    // 设置初始时间
    bus_time = 0;
}

BusControllerModel::~BusControllerModel()
{
    delete(rail_manager);
    delete(query_manager);
}

void BusControllerModel::ReadConfigFileSlot(const QString& file_name)
{
    ReadConfigFile(file_name.toStdString());
}

void BusControllerModel::AddQuerySlot(int query_type, int node_id) const
{
    rail_node_t *node_pos = rail_manager->FindNode(node_id);
    query_manager->CreateQuery(query_type, node_pos);
}

/*
 * 以下函数的实现移植自auto_pilot_bus
 * 源程序采用C写成
 */

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

    qDebug() << node_space_length << total_station;
    // 得到轨道的总长度
    total_distance = node_space_length * total_station;
    rail_manager->CreateRails(node_space_length, total_station);

    emit RailsCreated(total_station);
}

int BusControllerModel::FCFSDirection() const
{
    bus_query_t *p = query_manager->queries;

    if(p == nullptr)
    {
        return BUS_STOP;
    }   //如果没有请求，公交车停止

    else
    {
        int clockwise = 0;
        int counterclockwise = 0;   //用于顺，逆时针方向所经站台计数

        /**
         * 公交车当前所在位置
         */
        rail_node_t *now_position = rail_pos;
        /**
         * 公交车应该前进的方向
         */
        rail_node_t *target_position = p->node;

        rail_node_t *pos = now_position;
        while (pos != target_position) //顺时针计数
        {
            clockwise++;
            pos = pos->next_node;
        }

        pos = now_position;
        while (pos != target_position) //逆时针计数
        {
            counterclockwise++;
            pos = pos->last_node;
        }

        if(clockwise <= counterclockwise)
        {
            return BUS_CLOCK_WISE;
        }//若顺时针距离短(或顺逆相等)，公交车顺时针运行
        else
        {
            return BUS_COUNTER_CLOCK_WISE;
        }//若逆时针距离短，公交车逆时针运行
    }
}

bus_query_t *BusControllerModel::FCFSQuery() const
{
    bus_query_t *result = nullptr;

    if(query_manager->queries != nullptr)
    {
        if(rail_pos == query_manager->queries->node)
        {
            result = query_manager->queries;
        }
    }

    return result;
}

bus_query_t *BusControllerModel::SSTFGetQuery()
{
    // 当前没有请求
    if(query_manager->queries == nullptr)
    {
        return nullptr;
    }
    int length = 9999;
    bus_query_t *query = nullptr;
    bus_query_t *p = query_manager->queries;

    // 遍历顺时针方向
    // 在两个方向路程相同时选择顺时针方向
    // 所以先遍历顺时针方向
    while (p != nullptr)
    {
        int temp = GetQueryDistance(p, BUS_CLOCK_WISE);
        if(temp < length)
        {
            length = temp;
            query = p;
        }
        p = p->next_node;
    }

    // 遍历逆时针方向
    p = query_manager->queries;
    while (p != nullptr)
    {
        int temp = GetQueryDistance(p, BUS_COUNTER_CLOCK_WISE);
        if(temp < length)
        {
            length = temp;
            query = p;
        }
        p = p->next_node;
    }

    return query;
}

int BusControllerModel::SSTFDirection(bus_query_t *query)
{
    if (query == nullptr)
    {
        return BUS_STOP;
    }

    int length = GetQueryDistance(query, BUS_CLOCK_WISE);
    if(length > total_distance / 2)
    {
        return BUS_COUNTER_CLOCK_WISE;
    }
    else if(length == 0)
    {
        return BUS_STOP;
    }
    else
    {
        return BUS_CLOCK_WISE;
    }
}

bus_query_t *BusControllerModel::SSTFBTWQuery() const
{
    bus_query_t *query = query_manager->queries;
    bus_query_t *allow_query = nullptr;
    rail_node_t *now_node = rail_pos;

    while (query != nullptr)
    {
        if(query->node == now_node)
        {
            // 这里是设计上的缺陷，在bus_time显示时间的前一秒，公交车就实际上到达站台了
            if(query->time < bus_time - 1)
            {
                if(query->type == direction || query->type == BUS_TARGET)
                {
                    allow_query = query;
                    break;
                }
            }
        }
        query = query->next_node;
    }

    return allow_query;
}

bus_query_t *BusControllerModel::SCANGetQuery()
{
    // 当前没有请求
    if(query_manager->queries == nullptr)
    {
        return nullptr;
    }

    if(direction == BUS_STOP)
    {
        // 在停止的状态下第一次开始选择方向
        int length = 9999;
        bus_query_t *query = nullptr;
        bus_query_t *p = query_manager->queries;

        // 遍历顺时针方向
        // 在两个方向路程相同时选择顺时针方向
        // 所以先遍历顺时针方向
        while (p != nullptr)
        {
            int temp = GetQueryDistance(p, BUS_CLOCK_WISE);
            if(temp < length)
            {
                length = temp;
                query = p;
            }
            p = p->next_node;
        }

        // 遍历逆时针方向
        p = query_manager->queries;
        while (p != nullptr)
        {
            int temp = GetQueryDistance(p, BUS_COUNTER_CLOCK_WISE);
            if(temp < length)
            {
                length = temp;
                query = p;
            }
            p = p->next_node;
        }

        return query;
    }
    else
    {
        // 在已经有方向的情况下处理方向
        int length = 9999;
        bus_query_t *query = nullptr;
        bus_query_t *p = query_manager->queries;

        while (p != nullptr)
        {
            int temp = GetQueryDistance(p, direction);
            if(temp < length)
            {
                query = p;
                length = temp;
            }
            p = p->next_node;
        }

        return query;
    }
}

int BusControllerModel::SCANDirection(bus_query_t *query)
{
    if(query == nullptr)
    {
        return BUS_STOP;
    }

    if(direction == BUS_STOP)
    {
        int length = GetQueryDistance(query, BUS_CLOCK_WISE);
        if(length > total_distance / 2)
        {
            return BUS_COUNTER_CLOCK_WISE;
        }
        else
        {
            return BUS_CLOCK_WISE;
        }
    }
    else
    {
        int length = GetQueryDistance(query, direction);
        if(length > total_distance / 2)
        {
            if(direction == BUS_CLOCK_WISE)
            {
                return BUS_COUNTER_CLOCK_WISE;
            }
            else
            {
                return BUS_CLOCK_WISE;
            }
        }
        else
        {
            return direction;
        }
    }
}

bus_query_t *BusControllerModel::SCANBTWQuery() const
{
    rail_node_t *now_position = rail_pos;
    //获取公交车当前所在站点
    bus_query_t *p = query_manager->queries;

    while(p != nullptr)
    {
        if(p->node == now_position)
        {
            if(p->time < bus_time - 1)
            {
                return p;
            }
        }
        p = p->next_node;
    }//遍历请求链表，判断是否有可以顺便处理的请求

    return nullptr;
}


