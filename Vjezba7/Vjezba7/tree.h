#ifndef TREE_H
#define TREE_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024
#define MAX_DIRECTORY_LENGTH 1024
#define ERROR 1

#define PROGRAM_FAIL -1
#define PROGRAM_SUCCESS 0
#define EXIT 3

typedef struct Directory* Position;

typedef struct Directory {
    char name[MAX_DIRECTORY_LENGTH];
    Position child;
    Position sibling;
} Directory;
typedef struct stog* Poz;

typedef struct stog {
    Position adr;
    Poz next;
    Poz prev;
} Stog;

int initStog(Poz S);
int initDir(Position q);
int printMsg();
int consoleHandler(Position* Padr, Poz stack);
int makeDir(Position P, char name[MAX_DIRECTORY_LENGTH]);
Position insertDirectory(Position P, Position Q);
int changeDir(Position* Padr, Poz stack, char option[MAX_DIRECTORY_LENGTH]);
int printContent(Position P);
int printSiblings(Position Q);
int printPath(Poz stack, Position P);
int push(Poz prev, Position P);
Position pop(Poz prev);
int deleteTree(Position P);
int emptyStack(Poz stack, Position* root);

#endif