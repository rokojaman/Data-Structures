#include <stdlib.h>
#include <stdio.h>

#include "structs.h"

int headInit(Ptr head)
{
	strcpy(head->firstName, "HEAD ELEMENT");
	strcpy(head->lastName, "HEAD ELEMENT");
	head->points = 0;
	head->next = NULL;
	return EXIT_SUCCESS;
}

float calcRelativeScore(unsigned int apsoluteScore)
{
	return (float)100*apsoluteScore / MAX_EXAM_POINTS;
}

int printList(Ptr head)
{
	head = head->next;
	printf("%-20s %10s %10s\n", "FULL NAME", "POINTS", "SCORE");
	while (head != NULL)
	{
		printf("%s %-20s %-10d %-10f\n", head->firstName, head->lastName, head->points, head->relativeGrade);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int insertEnd(Ptr head, Student element)
{
	Ptr Q = (Ptr)malloc(sizeof(Student));
	if (!Q)
	{
		printf("Malloc error in insertEnd(Ptr head, Student element) function.\n");
		return MALLOC_ERROR;
	}
		
	while (head->next != NULL)
		head = head->next;

	strcpy(Q->firstName, element.firstName);
	strcpy(Q->lastName, element.lastName);
	Q->points = element.points;
	Q->relativeGrade = calcRelativeScore(element.points);
	head->next = Q;
	Q->next = NULL;

	return EXIT_SUCCESS;
}

int readFromFile(char fileName[MAX_STR_LENGTH], Ptr head)
{
	FILE* file = fopen(fileName, "r");
	Student element;
	char buffer[MAX_STR_LENGTH] = "\0";
	char name[MAX_STR_LENGTH] = "\0";
	char lastname[MAX_STR_LENGTH] = "\0";
	int points = 0;

	if (!file)
	{
		printf("Error opening file %s in function \
			readFromFile(char fileName[MAX_STR_LENGTH], Ptr head)\n", fileName);
		return FILE_OPEN_ERROR;
	}

	while (!feof(file))
	{
		fscanf(file, "%s %s %d", name, lastname, &points);
		strcpy(element.firstName, name);
		strcpy(element.lastName, lastname);
		element.points = points;
		element.next = NULL;
		insertEnd(head, element);
	}

	fclose(file);

	return EXIT_SUCCESS;
}

int deleteAll(Ptr head)
{
	Ptr temp = (Ptr)malloc(sizeof(Student));
	if (!temp)
	{
		printf("Malloc error in deleteAll(Ptr head) function");
		return MALLOC_ERROR;
	}	

	while (!head->next)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	free(head);

	return EXIT_SUCCESS;
}
