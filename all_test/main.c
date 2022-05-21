//
// Created by ricardo on 2022/5/20.
//
#include "bus_io.h"
#include "tools.h"

int main()
{
    /**
     * 输入的字符串
     */
    char input[30];
    /**
     * 输出的字符串
     */
    char output[150];
    /**
     * the_bus指针的本体
     */
    bus_t main_bus;
    /**
     * 公交车前进的方向
     */
    int direction;
    /**
     * 完成的请求
     */
    bus_query_t *finished_query;
    int index;
    char path[50];
    char read_output[150];
    FILE *input_file = NULL;
    FILE *output_file = NULL;

    printf("Please choose which test case to use:");
    scanf("%d\n", &index);

    ChooseTestCaseInput(path, index);
    input_file = fopen(path, "r");
    ChooseTestCaseOutput(path, index);
    output_file = fopen(path, "r");

    // 读取配置文件
    rails = ReadConfigFile();

    // 制造公交车
    the_bus = &main_bus;
    the_bus->distance = 0;
    the_bus->rail_node_pos = FindNode(rails, 1);

    // 开始时公交车应该是停下的
    direction = BUS_STOP;

    PrintState(output);
    ReadOutputFile(read_output, output_file);
    if(CheckOutput(output, read_output) == BUS_FAlSE)
    {
        printf("%s\n", output);
    }
    else
    {
        printf("%d Ok\n", bus_time);
    }

    for(;;)
    {
        fgets(input, sizeof input, input_file);

        int result = ReadInput(input);
        if(result == IO_CLOCK)
        {
            // 时间流动
            AddTime();

            switch (chosen_strategy)
            {
                case BUS_FCFS:
                    // 如果到站，处理请求和
                    if(JudgeOnStation() == BUS_TRUE)
                    {
                        direction = FCFSDirection();
                        finished_query = FCFSQuery();

                        if(finished_query != NULL) // 有请求就处理请求
                        {
                            // 循环处理所有可以处理的请求，总共消耗一秒
                            while (finished_query != NULL)
                            {
                                DeleteQuery(finished_query);
                                finished_query = FCFSQuery();
                            }
                        }
                        else //如果没有请求就继续前进
                        {
                            RunBus(direction);
                        }
                    }
                    else
                    {
                        RunBus(direction);
                    }
                    break;
                case BUS_SSTF:
                    break;
                case BUS_SCAN:
                    break;
                default:
                    break;
            }

            PrintState(output);
            ReadOutputFile(read_output, output_file);
            if(CheckOutput(output, read_output) == BUS_FAlSE)
            {
                printf("%s\n", output);
            }
            else
            {
                printf("%d Ok\n", bus_time);
            }

        }
        else if(result == IO_END)
        {
            printf("end\n");
            break;
        }
        else
        {
            //在读取到创建请求的情况下，不做任何事
        }
    }
}
