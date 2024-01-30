#ifndef FUNC_H
#define FUNC_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "list.h"

int importFileCountries(NodeP list, char* filename);
int importFileCities(TreeP* treehead, char* filename);
int displayFilteredTowns(NodeP list);
int getInputInt(int* val);
int getInputString(char* string);

#endif