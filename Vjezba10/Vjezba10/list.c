#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "list.h"
#include "consts.h"
#include "tree.h"

int InitListNode(NodeP node) {
	memset(node->CountryName, 0, MAX_STR_LEN);
	node->next = NULL;
	node->treehead = NULL;
	return EXIT_SUCCESS;
}
NodeP newListElement(NodeP list, char countryName[MAX_STR_LEN]) {

	NodeP Q = NULL;
	Q = malloc(sizeof(Node));
	if (!Q) {
		printf("Memory allocation fail!");
		return EXIT_FAILURE;
	}
	InitListNode(Q);
	strcpy(Q->CountryName, countryName);
	insertSorted(list, Q);

	return Q;
}
int insertSorted(NodeP list, NodeP Q) {
	NodeP temp = NULL;
	temp = list;

	while (temp->next != NULL && strcmp(Q->CountryName, temp->next->CountryName) > 0) {
		temp = temp->next;
	}
	if (temp != NULL) {
		Q->next = temp->next;
		temp->next = Q;
	}
	return EXIT_SUCCESS;
}
int printList(NodeP list) {
	NodeP temp;
	temp = list->next;
	setlocale(LC_CTYPE, "");
	if (!temp) {
		printf("List is empty!\n");
		return EXIT_FAILURE;
	}
	while (temp != NULL) {
		printf("Država: %s \n", temp->CountryName);
		printTreeinorder(temp->treehead);
		printf("\n");
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
NodeP findElByNodeName(NodeP list, char* name) {
	NodeP temp = list;

	while (temp != NULL) {
		if (strcmp(temp->CountryName, name) == 0)
			return temp;
		temp = temp->next;
	}
	return temp;
}
int deleteList(NodeP list) {
	int i = 0;

	if (!list) {
		printf("List is already empty, nothing to delete!");
		return EXIT_FAILURE;
	}
	while (list->next != NULL) {
		DelNextEl(list);
		i++;
	}
	if (i == 1) {
		printf("Deleted list! Deleted %i entry.\n", i);
	}
	else {
		printf("Deleted list! Deleted %i entries.\n", i);
	}
	return EXIT_SUCCESS;
}
int DelNextEl(NodeP list) {
	NodeP temp = NULL;

	if (list->next == NULL) {
		printf("\nElement was not found!\n");
		return EXIT_FAILURE;
	}
	temp = list->next;
	list->next = temp->next;
	temp->treehead = deleteTree(temp->treehead);
	free(temp);

	return EXIT_SUCCESS;
}