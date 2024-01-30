#define _CRT_SECURE_NO_WARNINGS
#include "polynomial.h"
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>

Position EndOfList(Position P) {

	while (P->Next != NULL) {
		P = P->Next;
	}
	return P;
}
Position PrevEl(Position P, Member M) {

	while (P->Next != NULL
		&& P->Next->Member.coefficient != M.coefficient
		&& P->Next->Member.exponent != M.exponent)
	{
		P = P->Next;
	}
	return P;
}

int NewElSort(Position P, Member M) {

	Position Poz = P;
	if (P == NULL) { return EXIT_FAILURE; }

	while (Poz->Next != NULL && Poz->Next->Member.exponent < M.exponent) {
		Poz = Poz->Next;
	}
	if (Poz->Next != NULL && Poz->Next->Member.exponent == M.exponent)
	{
		Poz->Next->Member.coefficient += M.coefficient;
		if (Poz->Next != NULL && Poz->Next->Member.coefficient == 0)
		{
			DelNextEl(Poz);
		}
		return EXIT_SUCCESS;
	}

	NewElAfter(Poz, M);
	return EXIT_SUCCESS;
}
int NewElAfter(Position P, Member M) {

	Position Q = malloc(sizeof(struct Cvor));

	if (Q == NULL)
	{
		printf("\n\nMemory allocation unsuccessful.\n\n\n");
		return EXIT_FAILURE;
	}

	Q->Member.coefficient = M.coefficient;
	Q->Member.exponent = M.exponent;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}
int NewElAfterEl(Position P, Member MA, Member M) {

	P = PrevEl(P, MA);
	NewElAfter(P->Next, M);
	printf("\n\nNew element created!\n\n\n");
	return EXIT_SUCCESS;
}
int NewElBeforeEl(Position P, Member MA, Member M) {

	P = PrevEl(P, MA);
	NewElAfter(P, M);
	printf("\n\nNew element created!\n\n\n");
	return EXIT_SUCCESS;
}
int NewElEnd(Position P, Member M) {
	P = EndOfList(P);
	NewElAfter(P, M);
	printf("\n\nNew element created!\n\n\n");
}
int PrintEl(Position P) {
	//P = P->Next;
	printf(" %ix^%i ", P->Member.coefficient, P->Member.exponent);
	return EXIT_SUCCESS;
}
int PrintList(Position P) {

	P = P->Next;

	if (P == NULL) {

		printf("\nList is empty!!\n");
		return EXIT_SUCCESS;
	}
	else {
		//printf("Polinom:");
		while (P != NULL) {

			PrintEl(P);
			P = P->Next;
			if (P != NULL) {
				printf("+");
			}
		}
		printf("\n");
	}
	return EXIT_SUCCESS;
}

int ReadFromFile(char nameOfFile[MAX_STR_LEN], Position Poz, int line)
{
	FILE* file = NULL;
	int  n, r, i;
	file = fopen(nameOfFile, "r");
	char buffer[MAX_STR_LEN] = { 0 };
	char* P = buffer;
	Member M;
	M.coefficient = 0;
	M.exponent = 0;
	n = 0; r = 0; i = 0;

	if (file == NULL) {
		printf("\n\nNemoguce otvoriti datoteku.\n\n");
		return EXIT_FAILURE;
	}
	while (i < line) {
		fgets(buffer, MAX_STR_LEN, file);
		i++;
	}

	while (strlen(buffer) > 0) {

		r = sscanf(P, " %d %d %n", &M.coefficient, &M.exponent, &n);
		if (r != 2) { printf("\nImported polinomial!\n\n"); break; }
		P += n * sizeof(char);
		NewElSort(Poz, M);
	}

	fclose(file);
	return EXIT_SUCCESS;
}
int Add(Position P1, Position P2, Position Zbroj) {
	Member M;
	M.coefficient = 0;
	M.exponent = 0;
	P1 = P1->Next;
	P2 = P2->Next;

	int i = 0;

	if (P1 == NULL || P2 == NULL)
	{
		printf("One of the lists is empty!");
		return EXIT_FAILURE;
	}
	while (P1 != NULL || P2 != NULL)
	{

		M.coefficient = 0;
		M.exponent = 0;
		if (P1->Member.exponent == P2->Member.exponent)
		{
			if (P1->Member.coefficient + P2->Member.coefficient != 0) {
				M.coefficient = P1->Member.coefficient + P2->Member.coefficient;
				M.exponent = P1->Member.exponent;
				NewElSort(Zbroj, M);
			}
			P1 = P1->Next; P2 = P2->Next;
		}
		while (P1 != NULL && (P2 == NULL || P1->Member.exponent < P2->Member.exponent))
		{
			NewElSort(Zbroj, P1->Member);
			P1 = P1->Next;
		}
		while (P2 != NULL && (P1 == NULL || P1->Member.exponent > P2->Member.exponent))
		{
			NewElSort(Zbroj, P2->Member);
			P2 = P2->Next;
			if (P2 == NULL) { break; }
		}
	}
	return EXIT_SUCCESS;
}

int Multiply(Position P1, Position P2, Position Multiple) {
	Member M;
	Position temp1, temp2;
	M.coefficient = 0;
	M.exponent = 0;
	temp1 = NULL;
	temp2 = NULL;
	P1 = P1->Next;
	P2 = P2->Next;
	temp1 = P1;
	temp2 = P2;

	if (P1 == NULL || P2 == NULL) {
		printf("One of the lists is empty!");
		return EXIT_FAILURE;
	}

	while (temp1 != NULL) {
		while (temp2 != NULL) {
			M.exponent = temp1->Member.exponent + temp2->Member.exponent;
			M.coefficient = temp1->Member.coefficient * temp2->Member.coefficient;
			temp2 = temp2->Next;
			NewElSort(Multiple, M);
			M.coefficient = 0;
			M.exponent = 0;
		}
		temp2 = P2;
		temp1 = temp1->Next;
	}
	return EXIT_SUCCESS;
}

int DelNextEl(Position P) {

	Position temp = NULL;

	if (P->Next == NULL) {

		printf("\nElement was not found!\n");
		return EXIT_FAILURE;
	}
	temp = P->Next;
	P->Next = P->Next->Next;

	free(temp);
	//printf("\nDeleted 1 element!\n");
	return EXIT_SUCCESS;
}
int DelAll(Position P) {

	int i = 0;
	if (P->Next == NULL)
	{
		printf("List is empty!! Success?\n");
		return EXIT_SUCCESS;
	}
	while (P->Next != NULL) {
		DelNextEl(P);
		i++;
	}
	printf("Deleted list! Deleted %i entries.\n", i);
	return EXIT_SUCCESS;
}
