#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "func.h"
#include "consts.h"
#include "list.h"

#define MAX_LINE_LEN 128
#define MAX_NUMBER_INT 10
#define MAX_STRING_LEN 128



int InitTreeNode(TreeP treeNode) {
	memset(treeNode->cityName, 0, MAX_STR_LEN);
	treeNode->popCount = 0;
	treeNode->left = NULL;
	treeNode->right = NULL;
	return EXIT_SUCCESS;
}
TreeP newTreeNode(TreeP P, char* cityName, int val)
{
	TreeP Q;
	Q = malloc(sizeof(Tree));
	if (Q == NULL)
	{
		printf("Insufficient ram space!");
		return P;
	}
	InitTreeNode(Q);
	Q->popCount = val;
	strcpy(Q->cityName, cityName);
	P = insertTreeNode(P, Q);
	return P;
}
TreeP insertTreeNode(TreeP P, TreeP Q) {
	if (P == NULL) return Q;
	if (Q->popCount > P->popCount) {
		P->right = insertTreeNode(P->right, Q);
		return P;
	}
	else if (Q->popCount < P->popCount) {
		P->left = insertTreeNode(P->left, Q);
		return P;
	}
	else if (Q->popCount == P->popCount) {
		if (strcmp(Q->cityName, P->cityName) > 0) {
			P->right = insertTreeNode(P->right, Q);
			return P;
		}
		else if (strcmp(Q->cityName, P->cityName) < 0) {
			P->left = insertTreeNode(P->left, Q);
			return P;
		}
		else {
			printf("City already in tree!\n");
			free(Q);
		}
	}
	return P;
}
int printNode(TreeP P)
{
	char a = ' ';
	setlocale(LC_CTYPE, "");
	if (P->popCount != 1)
		a = 'a';
	printf("%s: %i stanovnik%c\n", P->cityName, P->popCount, a);
	return EXIT_SUCCESS;
}
int printTreeinorder(TreeP P) {
	if (P == NULL) return EXIT_SUCCESS;
	printTreeinorder(P->left);
	printNode(P);
	printTreeinorder(P->right);
	return EXIT_SUCCESS;
}
int printTreeinorderAboveVal(TreeP P, int val) {
	if (P == NULL) return EXIT_SUCCESS;

	if (P->left && P->left->popCount > val) {
		printTreeinorderAboveVal(P->left, val);
	}
	if (P->popCount > val) {
		printNode(P);
	}
	if (P->right && P->right->popCount > val) {
		printTreeinorderAboveVal(P->right, val);
	}

	return EXIT_SUCCESS;
}
TreeP deleteTree(TreeP P) {
	if (P == NULL) {
		return NULL;
	}
	if (P->right) {
		P->right = deleteTree(P->right);
	}
	if (P->left) {
		P->left = deleteTree(P->left);
	}
	free(P);
	return NULL;
}