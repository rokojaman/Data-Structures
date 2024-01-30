#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "constants.h"

typedef struct _member {

	int coefficient;
	int exponent;

} Member;

struct Cvor;
typedef struct Cvor* Position;
typedef struct Cvor {

	Member Member;
	Position Next;

} Cvor;

Position PrevEl(Position P, Member O);
Position EndOfList(Position P);

int NewElSort(Position P, Member M);
int NewElAfter(Position P, Member M);
int NewElAfterEl(Position P, Member MA, Member M);
int NewElBeforeEl(Position P, Member MA, Member M);
int NewElEnd(Position P, Member M);
int PrintEl(Position P);
int PrintList(Position P);

int ReadFromFile(char nameOfFile[MAX_STR_LEN], Position Pozn, int line);
int Add(Position P1, Position P2, Position zbroj);
int Multiply(Position P1, Position P2, Position Multiple);

int DelNextEl(Position P);
int DelAll(Position P);

#endif