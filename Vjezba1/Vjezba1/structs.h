#ifndef STRUCTS_H
#define STRUCTS_H

#include "constants.h"

struct _student;
typedef struct _student* Ptr;

typedef struct _student {
	char firstName[MAX_STR_LENGTH];
	char lastName[MAX_STR_LENGTH];
	unsigned int points;
	float relativeGrade;
	Ptr next;
} Student;

int headInit(Ptr head);
float calcRelativeScore(unsigned int apsoluteScore);
int printList(Ptr head);
int insertEnd(Ptr head, Student element);
int readFromFile(char fileName[MAX_STR_LENGTH], Ptr head);
int deleteAll(Ptr head);

#endif