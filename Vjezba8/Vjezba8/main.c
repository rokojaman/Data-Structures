#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"


int main()
{
	int numbers[10] = { 2,5,7,8,11,1,4,2,3,7 };
	srand(time(NULL));

	Position head = NULL;
	FILE* fp = NULL;

	head = newTreeInput(head, numbers);

	if (openFile(&fp) != SUCCESS)
		return FAILURE;


	printf("Ispis inorder nakon input funkcije:\t");
	if (printTreeinorder(head))
		printf("No data!(Tree is empty)");
	printf("\n");

	fprintf(fp, "%s", "Stablo nakon insert funkcije:");
	printTreeinorderToFile(head, &fp);
	fprintf(fp, "%s", "\n\n");


	replace(head);


	printf("Ispis inorder nakon replace funkcije:\t");
	if (printTreeinorder(head))
		printf("No data!(Tree is empty)");
	printf("\n");

	fprintf(fp, "%s", "Stablo nakon replace funkcije:");
	printTreeinorderToFile(head, &fp);
	fprintf(fp, "%s", "\n\n");

	head = deletetree(head);
	fclose(fp);

	return 0;
}

