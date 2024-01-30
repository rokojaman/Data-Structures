#ifndef TREE_H
#define TREE_H

#define _CRT_SECURE_NO_WARNINGS
#include "consts.h"

typedef struct tree* TreeP;
typedef struct tree {
	char cityName[MAX_STR_LEN];
	int popCount;
	TreeP left;
	TreeP right;
}Tree;

int InitTreeNode(TreeP treeNode);
TreeP newTreeNode(TreeP P, char* cityName, int val);
TreeP insertTreeNode(TreeP P, TreeP Q);
int printNode(TreeP P);
int printTreeinorder(TreeP P);
int printTreeinorderAboveVal(TreeP P, int val);
TreeP deleteTree(TreeP P);

#endif