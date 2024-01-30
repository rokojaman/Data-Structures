#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int initStog(Poz S) {
	S->adr = NULL;
	S->next = NULL;
	S->prev = NULL;
	return PROGRAM_SUCCESS;
}
int initDir(Position q) {

	memset(q->name, 0, MAX_DIRECTORY_LENGTH);
	q->child = NULL;
	q->sibling = NULL;
	return PROGRAM_SUCCESS;
}
int printMsg() {

	printf(
		"\nCommannd prompt\n\n"
		"Supported operations:\n"
		"\tmd {folder_name}\n" // make folder
		"\tcd {folder_name}\n" // go to folder
		"\tcd ..\n" // go to parent folder
		"\tdir\n\n" // list all folders in current folder
	);
	return PROGRAM_SUCCESS;
}

int consoleHandler(Position* Padr, Poz stack)
{
	char buffer[MAX_BUFFER_SIZE] = "\0";
	char command[MAX_COMMAND_LENGTH] = "\0";
	char option[MAX_DIRECTORY_LENGTH] = "\0";
	char option2[MAX_DIRECTORY_LENGTH] = "\0";
	Position P;
	int n = 0;
	P = *Padr;

	memset(command, 0, MAX_COMMAND_LENGTH);
	memset(option, 0, MAX_DIRECTORY_LENGTH);
	memset(option2, 0, MAX_DIRECTORY_LENGTH);
	memset(buffer, 0, MAX_BUFFER_SIZE);

	printPath(stack, P);

	gets(buffer);

	n = sscanf(buffer, " %s %s %s", command, option, option2);
	if (n > 2) {
		printf("Too many arguments!\n");
		return PROGRAM_FAIL;
	}
	else if (strlen(command) < 2 && n == -1)
		return PROGRAM_FAIL;
	if (!strcmp(command, "dir"))
	{
		printContent(P);
		return PROGRAM_SUCCESS;
	}
	else if (!strcmp(command, "exit"))
	{
		return EXIT;
	}
	else if (!strcmp(command, "md") || !strcmp(command, "mkdir"))
	{
		return makeDir(P, option);
	}
	else if (!strcmp(command, "cd"))
	{
		changeDir(Padr, stack, option);
		return PROGRAM_SUCCESS;
	}
	printf("Unrecognized input!\n");
	return PROGRAM_SUCCESS;
}
int makeDir(Position P, char name[MAX_DIRECTORY_LENGTH]) {
	Position Q;
	Q = malloc(sizeof(Directory));
	if (Q == NULL)
	{
		printf("Insufficient ram space!");
		return PROGRAM_FAIL;
	}
	initDir(Q);
	strcpy(Q->name, name);
	P->child = insertDirectory(P->child, Q);
	return PROGRAM_SUCCESS;
}
Position insertDirectory(Position P, Position Q)
{
	if (P == NULL)
		return Q;
	if (strcmp(P->name, Q->name) == 0) {
		printf("Directory exists!\n");
		return P;
	}
	if (strcmp(P->name, Q->name) > 0)
	{
		Q->sibling = P;
		return Q;
	}

	P->sibling = insertDirectory(P->sibling, Q);
	return P;
}
int changeDir(Position* Padr, Poz stack, char option[MAX_DIRECTORY_LENGTH])
{
	Position Ptemp, P = *Padr;
	Ptemp = P->child;
	if (!strcmp(option, "..") && stack->next != NULL)
	{
		*Padr = pop(stack);
	}
	else
	{
		while (Ptemp != NULL) {
			if (!strcmp(option, Ptemp->name))
			{
				push(stack, P);
				*Padr = Ptemp;
				return PROGRAM_SUCCESS;
			}
			Ptemp = Ptemp->sibling;
		}
		if (Ptemp == NULL) {
			printf("Directory not found!\n");
		}
	}
	return PROGRAM_SUCCESS;
}
int printContent(Position P)
{
	return printSiblings(P->child);
}
int printSiblings(Position Q)
{
	if (Q == NULL) {
		return PROGRAM_SUCCESS;
	}

	printf("%s\n", Q->name);
	printSiblings(Q->sibling);
	//printf("%s\n", Q->name);

	Q = Q->sibling;

	return PROGRAM_SUCCESS;
}
int printPath(Poz stack, Position P)
{
	Poz stacktemp = stack->next;
	while (stacktemp != NULL && stacktemp->next != NULL) {
		stacktemp = stacktemp->next;
	}
	while (stacktemp != NULL && stacktemp->prev != NULL)
	{
		printf("%s\\", stacktemp->adr->name);
		stacktemp = stacktemp->prev;
	}
	printf("%s>", P->name);
	return PROGRAM_SUCCESS;
}
int push(Poz stack, Position P)
{
	Poz Q;
	Q = malloc(sizeof(Stog));
	if (Q == NULL)
	{
		return PROGRAM_FAIL;
	}
	initStog(Q);

	Q->prev = stack;
	Q->next = stack->next;
	stack->next = Q;
	if (Q->next != NULL)
		Q->next->prev = Q;
	Q->adr = P;

	return PROGRAM_SUCCESS;
}
Position pop(Poz stack)
{
	Poz temp;
	Position adr;
	adr = NULL; temp = NULL;

	temp = stack->next;
	if (temp->next != NULL)
		temp->next->prev = stack;
	stack->next = temp->next;
	adr = temp->adr;
	initStog(temp);
	free(temp);
	return adr;
}
int deleteTree(Position P)
{
	if (P == NULL)
		return PROGRAM_SUCCESS;
	deleteTree(P->child);
	deleteTree(P->sibling);
	free(P);
	return PROGRAM_SUCCESS;
}
int emptyStack(Poz stack, Position* root)
{
	while (stack->next != NULL) {
		*root = pop(stack);
	}
	return PROGRAM_SUCCESS;
}