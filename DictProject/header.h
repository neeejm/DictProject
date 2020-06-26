#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ELEMENT_SEP ';'
#define DEF_SEP '='
#define TYPE_SEP ':'
#define MAX_LETTERS 26

struct Word 
{
	char *word, *type, *def;
};
typedef struct Word Word;

struct Dict
{
	Word element;
	struct Dict *next;
};
typedef struct Dict Dict;

//dict.c
void create_all_lists (Dict **pdict);
int which_element (char l);
int count (Dict **pdict);
int count_by (Dict **pdict, char l);

//list.c
Dict* insert_start(Dict* head, Word element);
void print(Dict* head);
void free_dict (Dict **pdict);
void sort (Dict *head);
void print_by(Dict **pdict, char l);
void find(Dict **pdict, char *word, char mode);
void del (Dict **pdict, char l);
void save (Dict **pdict);

//test.c
void check_file (FILE* f);
void check_allocation (char *c);
_Bool is_word (char *word);