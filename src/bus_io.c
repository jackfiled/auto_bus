//
// Created by ricardo on 2022/5/6.
//
#include "bus_io.h"

int ReadInput(char *inputString)
{

    char src[20];
    int num;
    sscanf_s(inputString, "%[a-z] %d", src, &num);
    if (0 == strcmp("clock", src))
    {
        return IO_CLOCK;
    }
    else if (0 == strcmp("counterclockwise", src))
    {
        CreateQuery(BUS_COUNTER_CLOCK_WISE, FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("clockwise", src))
    {
        CreateQuery(BUS_CLOCK_WISE, FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("target", src))
    {
        CreateQuery(BUS_TARGET, FindNode(rails, num));
        return IO_READING;
    }
    else if (0 == strcmp("end", src))
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
    while (fgets(buffer, sizeof buffer, config_file) != NULL)
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
                if (*(p + 1) == '\n')
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

                if (*(p + 1) == '\n')
                {
                    distance = *p - 48;
                }

                break;
            default:
                continue;
        }

    }

    if (distance != 0 && total_station != 0)
    {
        return CreateRails(distance, total_station);
    }
    else
    {
        return NULL;
    }
}

void PrintState(char *str)
{
    memset(str, 0, 150);

    int count, flag = 1;  //flag用于标记，为使下面第一个循环能够进入
    rail_node_t *p = NULL;
    char target[25], clockwise[25], counterclockwise[25];

    for (count = 0, p = rails; flag == 1 || p != rails; p = p->next_node, count++)
    {
        flag=0;
        target[count] = '0';
        clockwise[count] = '0';
        counterclockwise[count] = '0';
    }   //遍历轨道链表，将所有站点初始化为0，即：无任何请求；

    bus_query_t *t = NULL;
    int i;
    for (t = queries; t != NULL; t = t->next_node)
    {
        i = t->node->id - 1;
        if (t->type == 0)
        {
            clockwise[i] = '1';
        }
        else if(t->time==BUS_COUNTER_CLOCK_WISE)
        {
            counterclockwise[i] = '1';
        }
        else if(t->type==BUS_TARGET)
        {
            target[i] = '1';
        }
    }   //遍历请求链表，将有请求的站点按照不同类型标记为1

    char line1[100], line2[10], line3[15], line4[100], line5[10], line6[100], line7[100];

    sprintf(line1, "TIME:%d\n", bus_time);
    sprintf(line2, "BUS:\n");
    sprintf(line3, "position:%d\n", GetBusPosition());
    sprintf(line4, "target:%s\n", target);
    sprintf(line5, "STATION:\n");
    sprintf(line6, "clockwise:%s\n", clockwise);
    sprintf(line7, "counterclockwise:%s\n", counterclockwise); //分别得到每一行的字符串

    strcat(line1, line2);
    strcat(line1, line3);
    strcat(line1, line4);
    strcat(line1, line5);
    strcat(line1, line6);
    strcat(line1, line7);//将7行字符串合并在一起

    strcat(str, line1);
}