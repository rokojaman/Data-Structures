#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "polynomial.h"

int main()
{
	Member Member1, Member2;
	Position head1, head2, zbroj, umnozak;

	Member1.exponent = 0; Member1.coefficient = 0;
	Member2.exponent = 0; Member2.coefficient = 0;
	head1 = malloc(sizeof(Cvor));
	head2 = malloc(sizeof(Cvor));
	zbroj = malloc(sizeof(Cvor));
	umnozak = malloc(sizeof(Cvor));

	if (head1 == NULL || head2 == NULL || zbroj == NULL || umnozak == NULL) {
		printf("Get more RAM\n");
		return EXIT_FAILURE;
	}
	head1->Next = NULL;
	head2->Next = NULL;
	zbroj->Next = NULL;
	umnozak->Next = NULL;

	ReadFromFile("poli.txt", head1, 1);
	PrintList(head1);
	ReadFromFile("poli.txt", head2, 2);
	PrintList(head2);

	Add(head1, head2, zbroj);
	Multiply(head1, head2, umnozak);

	printf("\nZbroj:");
	PrintList(zbroj);

	printf("\nUmnozak:");
	PrintList(umnozak);
	printf("\n");

	DelAll(head1);
	DelAll(head2);
	DelAll(zbroj);
	DelAll(umnozak);
	free(head1);
	free(head2);
	free(zbroj);
	free(umnozak);

	return EXIT_SUCCESS;
}