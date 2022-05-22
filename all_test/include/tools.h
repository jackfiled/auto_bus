//
// Created by ricardo on 2022/5/20.
//

#ifndef AUTO_PILOT_BUS_TOOLS_H
#define AUTO_PILOT_BUS_TOOLS_H
#include "stdio.h"
#include "string.h"
#include "define.h"
#include "rail.h"
#include "controller.h"

void ChooseTestCaseInput(char *path, int index);

void ChooseTestCaseOutput(char *path, int index);

rail_node_t *ChooseConfigFile(int index);

void ReadOutputFile(char *result, FILE *f);

int CheckOutput(char *program_output, char *read_output);

rail_node_t *ReadChosenConfigFile(char *config_file_path);
#endif //AUTO_PILOT_BUS_TOOLS_H
