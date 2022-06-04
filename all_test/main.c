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
    scanf("%d", &index);

    ChooseTestCaseInput(path, index);
    input_file = fopen(path, "r");
    ChooseTestCaseOutput(path, index);
    output_file = fopen(path, "r");

    // 读取配置文件
    rails = ChooseConfigFile(index);

    // 制造公交车
    the_bus = &main_bus;
    the_bus->distance = 0;
    the_bus->rail_node_pos = FindNode(rails, 1);

    // 开始时公交车应该是停下的
    direction = BUS_STOP;

    PrintStateInner(output);
    ReadOutputFile(read_output, output_file);
    if(CheckOutput(output, read_output) == BUS_FAlSE)
    {
        printf("Right:\n");
        printf("%s", read_output);
        printf("Wrong:\n");
        printf("%s", output);
        printf("\n"); // 打印一个空白作为分界线
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
                        direction = FCFSDirection(); //在开始得判断一次方向
                        finished_query = FCFSQuery();

                        if(finished_query != NULL) // 有请求就处理请求
                        {
                            // 循环处理所有可以处理的请求，总共消耗一秒
                            while (finished_query != NULL)
                            {
                                DeleteQuery(finished_query);
                                finished_query = FCFSQuery();
                            }

                            // 请求处理完再进行方向的判断
                            direction = FCFSDirection();
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
                    if(JudgeOnStation() == BUS_TRUE)
                    {
                        // 在没有目标请求的时候，获取一个目标站点
                        if(target_query == NULL)
                        {
                            target_query = SSTFGetQuery();
                            direction = SSTFDirection(target_query);

                            // 处理下一个需要处理的请求就在脚底下的情况
                            if(target_query != NULL && direction == BUS_STOP && target_query->node == the_bus->rail_node_pos)
                            {
                                while (target_query != NULL && direction == BUS_STOP && target_query->node == the_bus->rail_node_pos)
                                {
                                    DeleteQuery(target_query);
                                    target_query = SSTFGetQuery();
                                    direction = SSTFDirection(target_query);
                                }
                            }
                            RunBus(direction);
                        }
                        else
                        {
                            bus_query_t *btw_query = SSTFBTWQuery(direction);
                            // 如果到站了
                            if(target_query->node == the_bus->rail_node_pos)
                            {
                                // 如果刚好在站点上就有不少请求，处理一波
                                // 这里利用了&&运算符的短路特性，如果第一个判断为假，则不进行下一个判断，也就避免了段错误
                                while (target_query != NULL && target_query->node == the_bus->rail_node_pos)
                                {
                                    DeleteQuery(target_query);
                                    target_query = SSTFGetQuery();
                                    direction = SSTFDirection(target_query);
                                }
                            }
                            else if(btw_query != NULL)
                            {
                                // 如果没有到站就看看能不能顺便服务
                                while (btw_query != NULL)
                                {
                                    DeleteQuery(btw_query);
                                    btw_query = SSTFBTWQuery(direction);
                                }
                            }
                            else
                            {
                                // 如果啥也不能做就走吧
                                RunBus(direction);
                            }
                        }
                    }
                    else
                    {
                        // 没到站的话那就走吧
                        RunBus(direction);
                    }
                    break;
                case BUS_SCAN:
                    // 如果没有指定的请求就获得指定的请求
                    if(JudgeOnStation() == BUS_TRUE)
                    {
                        // 在没有目标请求的时候，获取一个目标站点
                        if(target_query == NULL)
                        {
                            target_query = SCANGetQuery(direction);
                            direction = SCANDirection(target_query, direction);

                            // 处理下一个需要处理的请求就在脚底下的情况
                            if(target_query != NULL && direction == BUS_STOP && target_query->node == the_bus->rail_node_pos)
                            {
                                while (target_query != NULL && direction == BUS_STOP && target_query->node == the_bus->rail_node_pos)
                                {
                                    DeleteQuery(target_query);
                                    target_query = SCANGetQuery(direction);
                                    direction = SCANDirection(target_query, direction);
                                }
                            }
                            RunBus(direction);
                        }
                        else
                        {
                            bus_query_t *btw_query = SCANBTWQuery();
                            // 如果到站了
                            if(target_query->node == the_bus->rail_node_pos)
                            {
                                // 如果刚好在站点上就有不少请求，处理一波
                                // 这里利用了&&运算符的短路特性，如果第一个判断为假，则不进行下一个判断，也就避免了段错误
                                while (target_query != NULL && target_query->node == the_bus->rail_node_pos)
                                {
                                    DeleteQuery(target_query);
                                    target_query = SCANGetQuery(direction);
                                    direction = SCANDirection(target_query, direction);
                                }
                            }
                            else if(btw_query != NULL)
                            {
                                // 如果没有到站就看看能不能顺便服务
                                while (btw_query != NULL)
                                {
                                    DeleteQuery(btw_query);
                                    btw_query = SCANBTWQuery();
                                }
                            }
                            else
                            {
                                // 如果啥也不能做就走吧
                                RunBus(direction);
                            }
                        }
                    }
                    else
                    {
                        // 没到站的话那就走吧
                        RunBus(direction);
                    }
                default:
                    // 这个分支只是为了符合代码规范而存在，理论上不会用到这个分支
                    break;
            }

            PrintStateInner(output);
            ReadOutputFile(read_output, output_file);
            if(CheckOutput(output, read_output) == BUS_FAlSE)
            {
                printf("Right:\n");
                printf("%s", read_output);
                printf("Wrong:\n");
                printf("%s", output);
                printf("\n"); // 打印一个空白行作为分界线
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
