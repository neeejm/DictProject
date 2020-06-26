#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "header.h"

int which_element (char l)
{
	int index = 0;

	switch(l)
	{
		case 'a':index = 1;break;
		case 'b':index = 2;break;
		case 'c':index = 3;break;
		case 'd':index = 4;break;
		case 'e':index = 5;break;
		case 'f':index = 6;break;
		case 'g':index = 7;break;
		case 'h':index = 8;break;
		case 'i':index = 9;break;
		case 'j':index = 10;break;
		case 'k':index = 11;break;
		case 'l':index = 12;break;
		case 'm':index = 13;break;
		case 'n':index = 14;break;
		case 'o':index = 15;break;
		case 'p':index = 16;break;
		case 'q':index = 17;break;
		case 'r':index = 18;break;
		case 's':index = 19;break;
		case 't':index = 20;break;
		case 'u':index = 21;break;
		case 'v':index = 22;break;
		case 'w':index = 23;break;
		case 'x':index = 24;break;
		case 'y':index = 25;break;
		case 'z':index = 26;break;
	}

	return index;
}

Word get_element (FILE * f, char c)
{
	Word element;
	char cara[2], temp[1000];

	strcpy(temp, "");
	cara[0] = c; cara[1] = '\0';
	strcat(temp, cara);

	while ((cara[0] = fgetc(f)) != ELEMENT_SEP)
	{
		// printf(">>>%c\n", cara[0]);

		if (cara[0] == TYPE_SEP)
		{
			element.word = (char *) malloc(strlen(temp) * sizeof(char));
			check_allocation(element.word);
			strlwr(temp);
			strcpy(element.word, temp);
			// puts(element.word);
			strcpy(temp, "");
			continue;
		}
		else if (cara[0] == DEF_SEP)
		{			
			element.type = (char *) malloc(strlen(temp) * sizeof(char));
			check_allocation(element.type);
			strlwr(temp);
			strcpy(element.type, temp);
			// puts(element.type);
			strcpy(temp, "");
			continue;
		}
		else
		{
			strcat(temp, cara);
			// printf("c: %c - %s\n", cara[0], temp);
		}		

	}

	element.def = (char *) malloc(strlen(temp) * sizeof(char));
	check_allocation(element.def);
	strlwr(temp);
	strcpy(element.def, temp);
	// puts(element.def);
	return element;
}

void create_all_lists (Dict **pdict)
{
	Word element;
	int i = 0;
	char c;
	
	FILE *my_file = fopen("files\\FrDict.txt", "r");
	// FILE *my_file = fopen("files\\FrDict2.txt", "r");
	check_file(my_file);

	while ((c = fgetc(my_file)) != EOF)
	{
		element = get_element(my_file, c);
		// printf("%s (%s) : %s\n", element.word, element.type, element.def);
		i = which_element(element.word[0]);		
		pdict[i - 1] = insert_start(pdict[i - 1], element);

		free(element.word);
		free(element.type);
		free(element.def);
	}

	fclose(my_file);
}

int count (Dict **pdict)
{
	int count = 0, i;
	Dict *temp;

	for (i = 0; i  < MAX_LETTERS; i++)
	{
		temp = pdict[i];

		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
	}	

	return count;
}

int count_by (Dict **pdict, char l)
{
	int count = 0, index = which_element(l);
	Dict *temp = pdict[index - 1];

	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	return count;
}