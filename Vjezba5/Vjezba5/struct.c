#define _CRT_SECURE_NO_WARNINGS

#include "constants.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>


int PrintEl(Position P) {
	printf("%f ", P->f);
	return EXIT_SUCCESS;
}

int PrintList(Position P) {

	P = P->next;

	if (P == NULL) {

		printf("\nList is empty!!\n");
		return EXIT_SUCCESS;
	}
	else {
		while (P != NULL) {
			PrintEl(P);
			P = P->next;
		}

		printf("\n");
	}
	return EXIT_SUCCESS;
}

int extractFromFile(char nameOfFile[MAX_STR_LEN], Position Poz)
{
	
	return EXIT_SUCCESS;
}


int DelAll(Position P) {

	int i = 0;
	if (P->next == NULL)
	{
		printf("List is empty!! Success?\n");
		return EXIT_SUCCESS;
	}
	while (P->next != NULL) {
		DelnextEl(P);
		i++;
	}
	if (i == 1) {
		printf("Deleted list! Deleted %i entry.\n", i);
	}
	else {
		printf("Deleted list! Deleted %i entries.\n", i);
	}

	return EXIT_SUCCESS;
}