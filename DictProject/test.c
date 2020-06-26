#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void check_file (FILE* f)
{
	if (f == NULL)
	{
		printf("!!! erreur de lecture de fichier\n");
		exit(1);
	}
}

void check_allocation (char *c)
{
	if (c == NULL)
	{
		printf("!!! erreur d'allocation\n");
		exit(2);
	}
}

_Bool is_word (char *word)
{
	int i;

	for (i = 0; i < strlen(word); i++)
	{	
		if ((word[i] < 'A' || word[i] > 'Z') && (word[i] < 'a' || word[i] > 'z'))
		{
			return false;
		}
	}
	return true;
}