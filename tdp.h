#ifndef TDP_H
#define TDP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "rdp.h"
#include "stack.h"
#include "tree.h"
#include "queue.h"

int** makeTable(int rows, int columns);
int getProduction(int** table, char symbol, char nonTerminal);
TREE tdp_Parse(char *input, int** parseTable);

#endif //TDP_H
