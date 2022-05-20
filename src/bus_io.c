//
// Created by ricardo on 2022/5/6.
//
#include "bus_io.h"

int ReadInput(char* inputString)
{
    
    char src[20];
    int num;
    sscanf_s(inputString,"%[a-z] %d",src,&num);
    if (0 == strcmp("clock",src))
    {
        return IO_CLOCK;
    }
    else if (0 == strcmp("counterclockwise",src))
    {
        CreateQuery(BUS_COUNTER_CLOCK_WISE, FindNode(rails ,num));
        return IO_READING;
    }
    else if (0 == strcmp("clockwise",src))
    {
        CreateQuery(BUS_CLOCK_WISE,FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("target",src))
    {
        CreateQuery(BUS_TARGET,FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("end",src))
    {
        return IO_END;
    }
    else
    {
        // 匹配失败则返回-1
        return -1;
    }
}

rail_node_t *ReadConfigFile()
{
    FILE *config_file = NULL;
    char buffer[30];
    int total_station = 0;
    int distance = 0;

    config_file = fopen("dict.dic", "r");

    // 循环读取文件的每一行
    while(fgets(buffer, sizeof buffer, config_file) != NULL)
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

                if(*p == '1' && *(p + 1) != '\n')
                {
                    total_station = 10;
                }
                else if(*(p + 1) == '\n')
                {
                    total_station = *p - 48;
                }

                break;
            case 'S':
                // STRATEGY
                p = buffer;
                // 将=前的字符全部略去
                while(*p != '=')
                {
                    p++;
                }
                // =也去掉
                p++;
                // =和策略之间的空格也去掉
                while(*p == ' ')
                {
                    p++;
                }

                if(*p == 'F' && *(p + 1) == 'C') //FCFS
                {
                    chosen_strategy = BUS_FCFS;
                }
                else if(*p == 'S' && *(p + 1) == 'S') //SSTF
                {
                    chosen_strategy = BUS_SSTF;
                }
                else if(*p == 'S' && *(p + 1) == 'C') //SCAN
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

                if(*(p + 1) == '\n')
                {
                    distance = *p - 48;
                }

                break;
            default:
                continue;
        }

    }

    if(distance != 0 && total_station != 0)
    {
        return CreateRails(distance, total_station);
    }
    else
    {
        return NULL;
    }
}
