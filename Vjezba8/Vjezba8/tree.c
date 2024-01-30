#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "constants.h"

//---------------------------funkcije za stablo (unos/inicijalizacija i sl)

int initNode(Position P)
{
	P->number = 0;
	P->right = NULL;
	P->left = NULL;
	return EXIT_SUCCESS;
}

Position newNode(int number)
{
	Position node = (Position)(malloc(sizeof(Node)));
	if (node == NULL) {
		printf("Insufficient ram space!");
		return node;
	}
	node->number = number;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Position insert(Position P, int number)
{
	if (P == NULL) {
		P = newNode(number);
		return P;
	}

	if (number >= P->number) {
		P->left = insert(P->left, number);
	}
	else if (number < P->number) {
		P->right = insert(P->right, number);
	}

	return P;
}

Position newTreeInput(Position P, int numbers[10])
{
	int num = 0, i = 0, choice = 10, n = 0;

	while (choice <= 0 || choice > 4) {
		printf("Unesite broj ispred opcije koju zelite odabrati:  \n");
		printf("(0)  Prekinuti program.\n");
		printf("(1)  Unijeti predefnirane brojeve u stablo.\n");
		printf("(2)  Rucno unijeti brojeve.\n");
		printf("(3)  Naumicno odabiranje n brojeva.\n");
		printf("Unos: ");
		getInput(&choice);
	}

	switch (choice)
	{
	default:
	case 0:
		break;
	case 1:
		while (i < 10) {
			P = insert(P, numbers[i]);
			i++;
		}
		break;
	case 2:
		printf("\nUnosite cijele brojeve koje zelite dodati u stablo.\n");
		printf("Nakon unosa elementa pritisnite enter.\n");
		printf("Za prekid unosa, unesite nesto sto nije broj.\n\n");

		printf("Unos: ");


		while (!getInput(&num))
		{
			printf("Unos: ");
			P = insert(P, num);
		}
		break;
	case 3:
		printf("\nn = ");
		getInput(&n);
		while (i < n) {
			P = insert(P, randNum());
			i++;
		}
		break;
	}


	return P;
}


// zadatak pod b replace



int replace(Position P)
{
	int tempnum = 0;
	if (P == NULL) {
		return 0;
	}
	tempnum = P->number;

	P->number = replace(P->left) + replace(P->right);

	return tempnum + P->number;
}


// zadatak pod c  rand


int randNum()
{
	return (rand() % (MAX_RANDOM - MIN_RANDOM + 1)) + MIN_RANDOM;
}

Position randomTree(Position P)
{
	int n = 0;
	int random = 0;
	int i = 0;

	printf("\nUnesite broj nasumicnih elemenata u stablu:\n");
	getInput(&n);

	for (i = 0; i < n; i++)
	{
		random = randNum();
		P = insert(P, random);
	}

	return P;
}


// print stabla


int printTreeinorder(Position P) {
	if (P == NULL) return EXIT_FAILURE;
	printTreeinorder(P->left);
	printNode(P);
	printTreeinorder(P->right);
	return EXIT_SUCCESS;
}
int printNode(Position P)
{
	printf("%d ", P->number);
	return EXIT_SUCCESS;
}


// stack funkcije te upis u datoteku 

int initStog(Poz S) {
	S->val = 0;
	S->next = NULL;
	return EXIT_SUCCESS;
}

int printTreeinorderToFile(Position P, FILE** fp) {
	Poz stack = malloc(sizeof(Stog));
	if (stack == NULL) {
		printf("Insufficient ram space!\n");
		return EXIT_FAILURE;
	}
	initStog(stack);

	pushTreeToStack(stack, P);

	popStackToFile(stack, *fp);
	free(stack);
	return EXIT_SUCCESS;
}
int pushTreeToStack(Poz stack, Position P) {
	if (P == NULL) return EXIT_FAILURE;

	pushTreeToStack(stack, P->left);
	push(stack, P->number);
	pushTreeToStack(stack, P->right);

	return EXIT_SUCCESS;
}
int push(Poz stack, int number) {
	Poz Q = malloc(sizeof(Stog));
	if (Q == NULL) {
		printf("Insufficient ram space!\n");
		return EXIT_FAILURE;
	}
	initStog(Q);

	Q->val = number;
	Q->next = stack->next;
	stack->next = Q;
	return EXIT_SUCCESS;
}
int popStackToFile(Poz stack, FILE* fp) {
	Poz temp = NULL;


	if (stack->next != NULL) {
		temp = stack->next;
		return EXIT_FAILURE;
	}
	while (temp != NULL)
	{
		stack->next = temp->next;
		fprintf(fp, " %i", temp->val);
		free(temp);
		temp = stack->next;
	}
	return EXIT_SUCCESS;
}


// funkcija za unos samo brojeva sa stdin

int getInput(int* number)
{
	*number = 0;
	char input[MAX_ARRAY_SIZE] = "\0";
	memset(input, 0, MAX_ARRAY_SIZE);

	fgets(input, sizeof(input), stdin);

	if (sscanf(input, " %i", number) == 1) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int openFile(FILE** fp) {
	char filename[MAX_FILENAME] = { '\0' };
	time_t result = time(NULL);
	struct tm tm = *localtime(&result);

	memset(filename, 0, MAX_FILENAME);
	sprintf(filename, "%s %d-%02d-%02d %02d-%02d-%02d", "Inorder printout ",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	*fp = fopen(filename, "a");
	if (fp == NULL) {
		printf("File not created!!");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//funkcija za brisanje stabla

Position deletetree(Position P) {
	if (P == NULL) {
		return NULL;
	}
	if (P->right) {
		P->right = deletetree(P->right);
	}
	if (P->left) {
		P->left = deletetree(P->left);
	}
	free(P);
	return NULL;
}