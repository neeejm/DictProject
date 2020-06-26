// DictProject.c
// Parcourir un fichier text et enregistrer chaque mot et sa signification dans un
// dictionnaire de mots.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "header.h"

#define MAX_OP 9

int main(int argc, char const *argv[])
{
	Dict **pdict = (Dict **) malloc(MAX_LETTERS * sizeof(Dict *));
	int i = 0, option = 0;
	char word[50], c[2];
	Word element;

	element.word = (char *) malloc(50 * sizeof(char));
	element.type = (char *) malloc(50 * sizeof(char));
	element.def = (char *) malloc(1000 * sizeof(char));

	for (i = 0; i < MAX_LETTERS; ++i)
		pdict[i] = NULL;
	
	create_all_lists(pdict);

	while (true)
	{
		printf("\n************************ Menu Dictionnaire Electronique *******************************************\n\n");
		printf("    1. Afficher la liste triee par ordre alphabetique des mots commencant par une lettre donnee.\n");
		printf("    2. Rechercher la signification d’un mot donnee.\n");
		printf("    3. Supprimer un mot donne.\n");
		printf("    4. Supprimer tous les mots commencant par une lettre donnee.\n");
		printf("    5. Ajouter au dictionnaire un mot donne ainsi que sa signification.\n");
		printf("    6. Compter le nombre de mots commencant par une lettre donnee.\n");
		printf("    7. Compter le nombre de mots du dictionnaire.\n");
		printf("    8. Sauvegarder.\n");
		printf("    9. Quitter.\n");
		printf("\n************************* Fin *********************************************************************\n\n");

	 	do
	 	{
	 		printf("Donnez votre option: ");
	 		scanf("%d", &option);
		}
		while (option < 1 || option > MAX_OP);

		switch (option)
		{
			case 1 :
				for (i = 0; i < MAX_LETTERS; i++)
				{
					sort(pdict[i]);
					c[0] = pdict[i]->element.word[0];
					strupr(c);
					printf("Liste %c: \n", c[0]);
					print(pdict[i]);
				}
				break;

			case 2:
				do
				{
					printf("Donnez le mot a rehercher (entrez 0 pour canceler): ");
					scanf("%s", word);
					if (strcmp(word, "0") == 0)
						goto BREAK2;
				}
				while (!is_word(word));
				strlwr(word);
				find(pdict, word, 'f');
				BREAK2:break;

			case 3:
				do
				{
					printf("Donnez le mot a supprimer (entrez 0 pour canceler): ");
					scanf("%s", word);
					if (strcmp(word, "0") == 0)
						goto BREAK3;
				}
				while (!is_word(word));
				strlwr(word);
				find(pdict, word, 'd');
				BREAK3:break;

			case 4:
				do
				{
					printf("Donnez une lettre (entrez 0 pour canceler): ");
					scanf("%s", word);
					if (strcmp(word, "0") == 0)
						goto BREAK4;
				}
				while (!is_word(word));
				strlwr(word);
				del(pdict, word[0]);
				BREAK4:break;

			case 5:
				do
				{
					printf("Donnez le nouveau mot (entrez 0 pour canceler): ");
					scanf("%s", element.word);
					if (strcmp(element.word, "0") == 0)
						goto BREAK5;
				}
				while (!is_word(element.word));
				strlwr(element.word);
				
				do
				{
					printf("Donnez son type (entrez 0 pour canceler): ");
					scanf("%s", element.type);
					if (strcmp(element.type, "0") == 0)
						goto BREAK5;
				}
				while (!is_word(element.type));

				printf("Donnez une definition au mot (entrez 0 pour canceler): ");
				scanf("%s", element.def);
				if (strcmp(element.def, "0") == 0)
					goto BREAK5;

				i = which_element(element.word[0]);
				pdict[i - 1] = insert_start(pdict[i - 1], element);
				printf(">>> ajoute\n");
				BREAK5:break;

			case 6:
				do
				{
					printf("Donnez une lettre (entrez 0 pour canceler): ");
					scanf("%s", word);
					if (strcmp(word, "0") == 0)
						goto BREAK6;
				}
				while (!is_word(word));
				strlwr(word);
				printf(">>> nombre de mots commencant par %c: %d\n", word[0], count_by(pdict, word[0]));
				BREAK6:break;

			case 7:
				printf(">>> nombre de mots du dictionnaire: %d\n", count(pdict));
				break;

			case 8:
				save(pdict);
				printf(">>> sauvgarde\n");
				break;

			case 9:
				goto END;
		}
		Sleep(1000);
	}

	END:
	free(element.word);
	free(element.type);
	free(element.def);
	free_dict(pdict);
	printf("Appuyez sur ENTRER pour sortir...");
	fflush(stdin);
	getchar(); 

	return 0;
}