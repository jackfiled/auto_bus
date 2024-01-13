//
// Created by ricardo on 2022/6/27.
//

#include "StrategyFactory.h"

BusStrategyBase *StrategyFactory::GetStrategy(const QString& file_name)
{
    char buffer[30];
    int total_station = 0;
    int distance = 0;
    int chosen_strategy = 0;

    FILE *file = fopen(file_name.toLatin1().data(), "r");

    // 循环读取文件的每一行
    while (fgets(buffer, 30, file) != nullptr)
    {
        const char first_char = buffer[0];
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
                    distance = *p - 48;
                }

                break;
            default:
                break;
        }
    }

    fclose(file);

    // 处理参数去缺省值的情况
    if (distance == 0)
    {
        distance = 2;
    }
    if (total_station == 0)
    {
        total_station = 5;
    }
    if(chosen_strategy == -1)
    {
        chosen_strategy = BUS_FCFS;
    }

    BusStrategyBase *controller;

    switch (chosen_strategy)
    {
        case BUS_FCFS:
            controller = new BusFCFSStrategy;
            break;
        case BUS_SSTF:
            controller = new BusSSTFStrategy;
            break;
        case BUS_SCAN:
            controller = new BusSCANStrategy;
            break;
        default:
            controller = nullptr;
            break;
    }

    controller->rails_model->CreateRails(distance, total_station);
    controller->strategy = chosen_strategy;
    return controller;
}
