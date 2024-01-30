#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* NE MICI HEAD. STAVI POINTER I STAVI MU VRIJEDNOST HEAD.
* CURRENT = HEAD
* ne usporeduj pointere (head == temp) vec njihov sadrzaj (name,lastname...)
* 
* 4. zadatak rijesi pomocu jednostruko vezane liste
*	-> sortirani unos
*	-> sscanf(buffer, "%dx^%d %n", n = kolicina memorije koja je procitana)
*		-> sscanf vraca broj procitanih elemenata (mora vratiti 2 jer ce citaju koeficijent i eksponent)
* 
* provjeri kako promijeniti boje u konzoli
*/

Ptr initElement(char firstName[MAX_STR_LENGTH], char lastName[MAX_STR_LENGTH], int year)
{
	Ptr temp = (Ptr)malloc(sizeof(Student));
	if (!temp)
	{
		printf("Unable to initialize element.\n");
		return MALLOC_ERROR;
	}
	strcpy(temp->firstName, firstName);
	strcpy(temp->lastName, lastName);
	temp->birthYear = year;
	temp->next = NULL;

	return temp;
}

int addToBeginning(Ptr head, Ptr element)
{
	element->next = head->next;
	head->next = element;
	return EXIT_SUCCESS;
}

int addToEnd(Ptr head, Ptr element)
{
	Ptr current = head;
	while (current->next)
		current = current->next;

	current->next = current;
	return 0;
}

int printList(Ptr head)
{
	Ptr current = head;
	if (current->next == NULL)
	{
		printf("Empty list.\n");
		return EXIT_SUCCESS;
	}
	printf("%20s%20s%20s", "First Name", "Last Name", "Year Of Birth\n");
	current = current->next;
	while (current) 
	{
		printf("%20s%20s%20d\n", current->firstName, current->lastName, current->birthYear);
		current = current->next;
	}
		
	return EXIT_SUCCESS;
}

int menu(Ptr head)
{
	int condition = TRUE;
	char choice = "\0";
	Ptr newNode = NULL;
	char firstName[MAX_STR_LENGTH] = "\0";
	char lastName[MAX_STR_LENGTH] = "\0";
	int birthYear = 0;

	while (condition)
	{
		printf("MENU\n");
		printf("a) New element at beginning\n");
		printf("b) New element at end\n");
		printf("c) Print list\n");
		printf("d) Find element\n");
		printf("e) Delete element\n");
		printf("f) Add element after another\n");
		printf("g) Add element before another\n");
		printf("j) Print elements to file\n");
		printf("k) Insert elements from file\n");
		printf("x) Exit\n");
		scanf(" %c", &choice);

		switch (choice)
		{
		// add element at beginning
		case 'A':
		case 'a':
		{
			printf("Enter first name, last name and year of birth.\n");
			scanf(" %s %s %d", firstName, lastName, &birthYear);
			newNode = initElement(firstName, lastName, birthYear);
			addToBeginning(head, newNode);
			break;
		}
		// add element at end
		case 'B':
		case 'b':
		{
			printf("Enter first name, last name and year of birth.\n");
			scanf(" %s %s %d", firstName, lastName, &birthYear);
			newNode = initElement(firstName, lastName, birthYear);
			addToEnd(head, newNode);
			break;
		}

		// print list
		case 'C':
		case 'c':
		{
			printList(head);
			break;
		}

		// find element
		case 'D':
		case 'd':
		{
			printf("Insert last name:\n");
			scanf(" %s", lastName);
			Ptr newNode = findElement(head, lastName);
			if (!newNode)
			{
				printf("Element not found.\n");
			}
			else
			{
				printf("Element found! Details:\n");
				printf("First name: %s \nLast name: %s", newNode->firstName, newNode->lastName);
				printf("Year of birth: %d\n", newNode->birthYear);
			}
			break;
		}
		
		// delete element
		case 'E':
		case 'e':
		{
			printf("Enter last name:\n");
			char name[MAX_STR_LENGTH] = { 0 };
			scanf(" %s", name);
			deleteElement(head, name);
			break;
		}

		// insert after
		case 'F':
		case 'f':
		{
			printf("Enter first name, last name and year of birth:\n");
			char firstname[MAX_STR_LENGTH] = { 0 };
			char lastname[MAX_STR_LENGTH] = { 0 };
			int yearOfBirth = 0;
			Ptr element = NULL;
			scanf(" %s %s %d", firstname, lastname, &yearOfBirth);

			element = initElement(firstname, lastname, yearOfBirth);
			printf("Enter the last name to insert after:\n");
			memset(lastname, "\0", sizeof(lastname));
			scanf(" %s", lastname);
			insertAfter(head, element, lastname);
			break;
		}

		// insert before
		case 'G':
		case 'g':
		{
			printf("Enter first name, last name and year of birth:\n");
			char firstname[MAX_STR_LENGTH] = { 0 };
			char lastname[MAX_STR_LENGTH] = { 0 };
			int yearOfBirth = 0;
			Ptr element = NULL;
			scanf(" %s %s %d", firstname, lastname, &yearOfBirth);

			element = initElement(firstname, lastname, yearOfBirth);
			printf("Enter the last name to insert after:\n");
			memset(lastname, "\0", sizeof(lastname));
			scanf(" %s", lastname);
			insertBefore(head, element, lastname);
			break;
		}

		// print to .txt file
		case 'J':
		case 'j':
		{
			printToFile(head);
			break;
		}

		// insert from .txt file
		case 'K':
		case 'k':
		{
			addFromFile(head);
			break;
		}

		// exit		
		case 'X':
		case 'x':
			condition = FALSE;
			break;

		default:
			printf("Command not found.\n");			
		}
	}

	return EXIT_SUCCESS;
}

int deleteAll(Ptr head)
{
	Ptr temp = NULL;
	temp = head->next;
	
	while (temp)
	{
		head->next = temp->next;
		free(temp);
		temp = head->next;
	}
	free(head);

	return EXIT_SUCCESS;
}

Ptr findElement(Ptr head, char name[MAX_STR_LENGTH])
{
	Ptr current = head->next;
	while (NULL != current)
	{
		if (!strcmp(current->lastName, name))
			return current;
		current = current->next;
	}
	return NULL;
}

int deleteElement(Ptr head, char name[MAX_STR_LENGTH])
{
	Ptr temp = NULL;
	Ptr current = head;
	temp = findElement(head, name);
	if (!temp)
	{
		return EXIT_FAILURE;
	}

	while (current->next != NULL && current->next != temp)
		current = current->next;
	current->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int insertAfter(Ptr head, Ptr element, char name[MAX_STR_LENGTH])
{
	while (head->next != NULL && !strcmp(head->lastName, name))
		head = head->next;
	element->next = head->next;
	head->next = element;

	return EXIT_SUCCESS;
}

int insertBefore(Ptr head, Ptr element, char name[MAX_STR_LENGTH])
{
	Ptr temp = findElement(head, name);
	while (head->next != NULL)
	{
		if (head->next == temp)
			break;

		head = head->next;
	}
		
	temp = head->next;
	head->next = temp;

	return EXIT_SUCCESS;
}

int printToFile(Ptr head)
{
	char filename[MAX_STR_LENGTH] = { 0 };
	FILE* newFile = NULL;
	Ptr current = head->next;

	printf("Enter file name:\n");
	scanf("%s", filename);

	newFile = fopen(filename, "w");
	if (!filename)
	{
		printf("Unable to open file.\n");
		return FILE_OPEN_ERROR;
	}
	while (current != NULL)
	{
		fprintf(newFile, "%s %s %d\n", current->lastName, current->firstName, current->birthYear);
		current = current->next;
	}
	fclose(filename);

	return EXIT_SUCCESS;
}

int addFromFile(Ptr head)
{
	char filename[MAX_STR_LENGTH] = { 0 };
	char firstname[MAX_STR_LENGTH] = { 0 };
	char lastname[MAX_STR_LENGTH] = { 0 };
	int birthyear = 0;
	Ptr element = NULL;
	FILE* newFile = NULL;
	int status = 0;
	printf("Enter file name:\n");
	scanf(" %s", filename);

	if (strstr(filename, ".txt"))
	{
		printf("File name must contain extension .txt.\n");
		return EXIT_FAILURE;
	}

	newFile = fopen(filename, "r");
	if (!filename)
	{
		printf("Unable to open file.\n");
		return FILE_OPEN_ERROR;
	}

	while (!feof(newFile))
	{
		status = fscanf(newFile, "%s %s %d", firstname, lastname, &birthyear);
		if (status != 3)
		{
			printf("Unable to read.\n");
			return EXIT_FAILURE;
		}
		element = initElement(firstname, lastname, birthyear);
		addToBeginning(head, element);
	}

	fclose(newFile);
	return EXIT_SUCCESS;
}
