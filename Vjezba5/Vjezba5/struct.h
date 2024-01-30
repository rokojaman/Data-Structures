#ifndef STRUCT_H
#define STRUCT_H

#include "constants.h"

struct _element;
typedef struct _element* Position;
typedef struct _element {

	float f;
	Position next;

} Element;

int PrintEl(Position P);
int PrintList(Position P);
int extractFromFile(char nameOfFile[MAX_STR_LEN], Position Poz);
int DelAll(Position P);


#endif