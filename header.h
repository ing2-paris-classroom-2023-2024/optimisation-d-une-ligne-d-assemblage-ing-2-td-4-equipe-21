

//
// Created by perron on 12/3/2023.
//


#ifndef VERSION_PC_PRE_H
#define VERSION_PC_PRE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_OPERATIONS 100


typedef struct {
    char op[10];
} Operation;


void dfs(int node);
#endif //VERSION_PC_PRE_H
