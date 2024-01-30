#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "constants.h"

int main()
{
	Ptr head = (Ptr)malloc(sizeof(Student));
	if (!head)
		return MALLOC_ERROR;

	memset(head->firstName, 0, sizeof(head->firstName));
	memset(head->lastName, 0, sizeof(head->lastName));
	head->birthYear = 0;
	head->next = NULL;
	menu(head);

	deleteAll(head);

	return EXIT_SUCCESS;
}