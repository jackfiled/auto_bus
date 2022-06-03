#include "bus_io.h"

/**
 * @brief 程序的主函数
 * 
 * @return int 程序结束的状态，0表示成功
 */
int main()
{
    /**
     * 输入的字符串
     */
    char input[30];
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

    // 读取配置文件
    rails = ReadConfigFile();

    // 制造公交车
    the_bus = &main_bus;
    the_bus->distance = 0;
    the_bus->rail_node_pos = FindNode(rails, 1);

    // 开始时公交车应该是停下的
    direction = BUS_STOP;

    PrintState();

    for(;;)
    {
        fgets(input, sizeof input, stdin);

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
                    // 如果没有指定的请求就获得指定的请求
                    if(target_query == NULL)
                    {
                        target_query = SSTFGetQuery();
                        direction = SSTFDirection(target_query);
                    }

                    if(JudgeOnStation() == BUS_TRUE)
                    {
                        // 如果到达目标的站点
                        if(the_bus->rail_node_pos == target_query->node)
                        {
                            DeleteQuery(target_query);
                            target_query = NULL;
                        }
                        else
                        {
                            // 处理可以顺便处理的请求
                            bus_query_t *btw_query = SSTFBTWQuery(direction);
                            if (btw_query != NULL)
                            {
                                while (btw_query != NULL)
                                {
                                    DeleteQuery(btw_query);
                                    btw_query = SSTFBTWQuery(direction);
                                }
                            }
                            else
                            {
                                RunBus(direction);
                            }
                        }
                    }
                    else
                    {
                        RunBus(direction);
                    }
                    break;
                case BUS_SCAN:
                    // 如果没有指定的请求就获得指定的请求
                    if(target_query == NULL)
                    {
                        target_query = SCANGetQuery(direction);
                        direction = SCANDirection(target_query);
                    }

                    if(JudgeOnStation() == BUS_TRUE)
                    {
                        // 如果到达目标的站点
                        if(the_bus->rail_node_pos == target_query->node)
                        {
                            DeleteQuery(target_query);
                            target_query = NULL;
                        }
                        else
                        {
                            bus_query_t *btw_query = SCANBTWQuery();
                            // 处理可以顺路处理的请求
                            if(btw_query != NULL)
                            {
                                while (btw_query != NULL)
                                {
                                    DeleteQuery(btw_query);
                                    btw_query = SCANBTWQuery();
                                }
                            }
                            else
                            {
                                RunBus(direction);
                            }
                        }
                    }
                    else
                    {
                        RunBus(direction);
                    }
                    break;
                default:
                    // 这个分支只是为了符合代码规范而存在，理论上不会用到这个分支
                    break;
            }
            PrintState();
        }
        else if(result == IO_END)
        {
            printf("end\n");

            FreeRails(rails);
            FreeQueries(queries);
            break;
        }
        else
        {
            //在读取到创建请求的情况下，不做任何事
        }
    }

    return 0;
}