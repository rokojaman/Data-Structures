#pragma once
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
#define MAX_RANDOM 89
#define MIN_RANDOM 11
#define SUCCESS 0
#define FAILURE 1
#define MAX_NUMBER_INT 128
#define MAX_FILENAME 64


typedef struct node* Position;

typedef struct node
{
	int number;
	Position left;
	Position right;
} Node;

typedef struct stog* Poz;

typedef struct stog {
	int val;
	Poz next;
} Stog;

//  funkcije za stablo (unos/inicijalizacija i sl)
int initNode(Position P);
Position newNode(int value);
Position insert(Position P, int number);
Position newTreeInput(Position P, int numbers[10]);

// zadatak pod b replace

int replace(Position P);

// zadatak pod c  rand

int randNum();
Position randomTree(Position P);

// print stabla

int printTreeinorder(Position P); // inorder ispis
int printNode(Position P);

// stack funkcije te upis u datoteku

int initStog(Poz S);
int printTreeinorderToFile(Position P, FILE** fp);
int pushTreeToStack(Poz stack, Position P);
int push(Poz stack, int val);
int popStackToFile(Poz stack, FILE* fp);

// funkcija za unos samo brojeva sa stdin

int getInput(int* val);
int openFile(FILE** fp);

//funkcija za brisanje stabla

Position deletetree(Position P);