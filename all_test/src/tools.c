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