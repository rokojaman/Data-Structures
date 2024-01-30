#ifndef LIST_H
#define LIST_H


#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"
#include "consts.h"

typedef struct node* NodeP;
typedef struct node {
	char CountryName[MAX_STR_LEN];
	TreeP treehead;
	NodeP next;
}Node;

int InitListNode(NodeP node);
NodeP newListElement(NodeP list, char countryName[MAX_STR_LEN]);
int insertSorted(NodeP list, NodeP Q);
int printList(NodeP list);
NodeP findElByNodeName(NodeP list, char* name);
int deleteList(NodeP list);
int DelNextEl(NodeP list);

#endif