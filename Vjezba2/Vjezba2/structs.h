#ifndef STRUCTS_H
#define STRUCTS_H

#include "constants.h"

struct _student;
typedef struct _student* Ptr;
typedef struct _student {
	char firstName[MAX_STR_LENGTH];
	char lastName[MAX_STR_LENGTH];
	int birthYear;
	Ptr next;
} Student;

Ptr initElement(char firstName[MAX_STR_LENGTH], char lastName[MAX_STR_LENGTH], int year);
int addToBeginning(Ptr head, Ptr element);
int addToEnd(Ptr head, Ptr element);
int printList(Ptr head);
int menu(Ptr head);
int deleteAll(Ptr head);
Ptr findElement(Ptr head, char name[MAX_STR_LENGTH]);
int deleteElement(Ptr head, char name[MAX_STR_LENGTH]);
int insertAfter(Ptr head, Ptr element, char name[MAX_STR_LENGTH]);
int insertBefore(Ptr head, Ptr element, char name[MAX_STR_LENGTH]);
int printToFile(Ptr head);
int addFromFile(Ptr head);
int studentCompare(Ptr first, Ptr second);

#endif