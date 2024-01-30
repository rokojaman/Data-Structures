#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


int main()
{
    int returnVal;
    Position root;
    Poz stack;
    returnVal = 0;


    stack = malloc(sizeof(Stog));
    if (stack == NULL)
    {
        printf("Insufficient ram space!");
        return PROGRAM_FAIL;
    }
    initStog(stack);

    root = malloc(sizeof(Directory));
    if (root == NULL)
    {
        printf("Insufficient ram space!");
        return PROGRAM_FAIL;
    }
    initDir(root);

    strcpy(root->name, "D:");

    printMsg();

    while (returnVal != EXIT) {
        returnVal = consoleHandler(&root, stack);
    }
    emptyStack(stack, &root);
    deleteTree(root);
    free(stack);
    return PROGRAM_SUCCESS;
}