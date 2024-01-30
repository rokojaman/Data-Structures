#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int main() 
{
	int errorMessage = 0;
	Ptr head = (Ptr)malloc(sizeof(Student));
	if (!head)
		return MALLOC_ERROR;

	headInit(head);
	errorMessage = readFromFile("studenti.txt", head);
	if (errorMessage)
		return EXIT_FAILURE;
	printList(head);
	deleteAll(head);

	return 0;
}