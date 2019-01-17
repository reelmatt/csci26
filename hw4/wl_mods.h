/*
 *	data structure for this unit:  a linked list of structs
 */
struct link {
		char *word;         /* the string */
		int value;          /* the count */
		struct link *next;  /* the next one */
};

//Define a shorthand for 'struct link
typedef struct link LINK;

//For wlfiler6.c
#define ARRAY_SIZE 26
LINK * find_link(char *word);

//For wldata.c
char * new_string();
char * cp_string(char *str);
LINK * new_link(char *str, int val);

//For wlmain_mod.c -- read_word and helper functions
char * read_word();
char first_char();
int valid_char(char);