#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "header.h"

Dict* insert_start (Dict *head, Word element)
{		
	Dict *e = (Dict *) malloc(sizeof(Dict));

	e->element.word = (char *) malloc(strlen(element.word) * sizeof(char));
	e->element.type = (char *) malloc(strlen(element.type) * sizeof(char));
	e->element.def = (char *) malloc(strlen(element.def) * sizeof(char));

	strcpy(e->element.word, element.word);
	strcpy(e->element.type, element.type);
	strcpy(e->element.def, element.def);
	e->next = head;
	head = e;

	return head;
}

void sort (Dict *head)
{
	Dict *i = head, *j;
	Word temp;

	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (strcmp(i->element.word,j->element.word) > 0)
			{
				temp = i->element;
				i->element = j->element;
				j->element =  temp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

void free_dict (Dict **pdict)
{
	int i;
	Dict *temp, *del;

	for (i = 0; i < MAX_LETTERS; i++)
	{
		temp = pdict[i];
		while (temp != NULL)
		{
			del = temp;
			temp = temp->next;
			free(del->element.word);
			free(del->element.type);
			free(del->element.def);
			free(del);
		}
	}
	free(pdict);
}

Dict* rmv(Dict* head, int index)
{
	Dict* tmp = head;
	Dict* del;

	if (index == 1)
	{
		del = tmp;
		tmp = del->next;
		free(del->element.word);
		free(del->element.type);
		free(del->element.def);
		free(del);
		return tmp;
	}

	int i;
	for (i = 0; i < index - 2; i++)
		tmp = tmp->next;

	del = tmp->next;
	tmp->next = del->next;
	free(del->element.word);
	free(del->element.type);
	free(del->element.def);
	free(del);
	return head;
}

void del (Dict **pdict, char l)
{
	int index = which_element(l);
	Dict *del;

	while (pdict[index - 1] != NULL)
	{
		del = pdict[index - 1];
		pdict[index - 1] = pdict[index - 1]->next;
		free(del->element.word);
		free(del->element.type);
		free(del->element.def);
		free(del);
	}
	pdict[index - 1] = NULL;
	printf(">>> tous les mots commencant par %c sont supprimes\n", l);
}

void print(Dict *head)
{
	Dict* temp = head;

	while(temp != NULL)
	{
		// printf("%s (%s) : %s\n", temp->element.word, temp->element.type, temp->element.def);
		printf("%s (%s) :\n____ %s\n\n", temp->element.word, temp->element.type, temp->element.def);
		temp = temp->next;
	}
	printf("\n");
}

void print_by(Dict **pdict, char l)
{
	int index = which_element(l);
	Dict* temp = pdict[index -  1];

	print(temp);
}

void find(Dict **pdict, char *word, char mode)
{
	int index = 0, count = 0;
	Dict* temp;
	
 	index = which_element(word[0]);
 	temp = pdict[index -  1];

	while (temp != NULL)
	{
		count++;
		if (strcmp(temp->element.word, word) == 0)
		{
			if (mode == 'f') //print the given word
			{
				printf("%s (%s) : %s\n", temp->element.word, temp->element.type, temp->element.def);
				return;
			}
			else if (mode == 'd') //delete the given word
			{
			 	pdict[index -  1] = rmv(pdict[index -  1], count);
			 	printf(">>> supprime\n");
				return;
			}
		}
		temp = temp->next;
	}
	printf(">>> %s n'existe pas\n", word);
}

void save (Dict **pdict)
{
	Dict *temp;
	char c;
	int i, j;

	FILE *file_copy = fopen("files\\FrDictOld.txt", "w");
	check_file(file_copy);
	FILE *my_file = fopen("files\\FrDict.txt", "r");
	check_file(my_file);

	while ((c = fgetc(my_file)) != EOF)
		fputc(c, file_copy);

	fclose(file_copy);
	fclose(my_file);

	my_file = fopen("files\\FrDict.txt", "w");

	for (i = 0; i < MAX_LETTERS; i++)
	{
		temp = pdict[i];

		while (temp != NULL)
		{
			for (j = 0; j < strlen(temp->element.word); j++)
				fputc(temp->element.word[j], my_file);
			fputc(':', my_file);
			for (j = 0; j < strlen(temp->element.type); j++)
				fputc(temp->element.type[j], my_file);
			fputc('=', my_file);
			for (j = 0; j < strlen(temp->element.def); j++)
				fputc(temp->element.def[j], my_file);
			fputc(';', my_file);

			temp  = temp->next;
		}
	}
	fclose(my_file);
}