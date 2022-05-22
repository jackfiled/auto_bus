//
// Created by ricardo on 2022/5/20.
//
#include "tools.h"

void ChooseTestCaseInput(char *path, int index)
{
    memset(path, 0, 50);

    char root_path[] = "./test_cases/";
    char input_file[] = "/input.txt";
    char case_path[3];

    sprintf(case_path, "%d", index);

    strcat(path, root_path);
    strcat(path, case_path);
    strcat(path, input_file);
}

void ChooseTestCaseOutput(char *path, int index)
{
    memset(path, 0, 50);

    char root_path[] = "./test_cases/";
    char output_file[] = "/output.txt";
    char case_path[3];

    sprintf(case_path, "%d", index);

    strcat(path, root_path);
    strcat(path, case_path);
    strcat(path, output_file);
}

void ReadOutputFile(char *result, FILE *f)
{
    memset(result, 0, 150);

    for(size_t i = 0; i < 7; i++)
    {
        char temp[50];
        fgets(temp, 50, f);
        strcat(result, temp);
    }
}

int CheckOutput(char *program_output, char *read_output)
{
    int result = strcmp(program_output, read_output);

    if(result == 0)
    {
        return BUS_TRUE;
    }
    else
    {
        return BUS_FAlSE;
    }
}

rail_node_t *ChooseConfigFile(int index)
{
    char root_path[] = "./test_cases/";
    char config_path[] = "/dict.dic";
    char case_path[3];

    sprintf(case_path, "%d", index);

    char file_path[30];

    strcat(file_path, root_path);
    strcat(file_path, case_path);
    strcat(file_path, config_path);

    return ReadChosenConfigFile(file_path);
}

rail_node_t *ReadChosenConfigFile(char *config_file_path)
{
    FILE *config_file = NULL;
    char buffer[30];
    int total_station = 0;
    int distance = 0;

    config_file = fopen(config_file_path, "r");

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

                if (*p == '1' && *(p + 1) != '\n')
                {
                    total_station = 10;
                }
                else if (*(p + 1) == '\n')
                {
                    total_station = *p - 48;
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