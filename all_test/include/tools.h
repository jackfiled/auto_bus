//
// Created by ricardo on 2022/5/20.
//

#ifndef AUTO_PILOT_BUS_TOOLS_H
#define AUTO_PILOT_BUS_TOOLS_H
#include "stdio.h"
#include "string.h"
#include "define.h"

void ChooseTestCaseInput(char *path, int index);

void ChooseTestCaseOutput(char *path, int index);

void ReadOutputFile(char *result, FILE *f);

int CheckOutput(char *program_output, char *read_output);
#endif //AUTO_PILOT_BUS_TOOLS_H
