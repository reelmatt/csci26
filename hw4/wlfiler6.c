#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wl.h"
#include "wl_mods.h"

/*
 *	wlfiler6.c
 *
 *  starter code copied from wlfiler5.c from class
 *  modifications made by Matthew Thomas
 *
 *	functions are:
 *      init_table()     - set up the table[] of linked lists
 *		in_table(str)    - sees if word is in table
 *		insert(str,val)  - insert value into table
 *		lookup(str)      - retrieve value
 *		update(str,val)  - update value in table
 *		firstword()      - return first word in table
 *		nextword()       - return next word in table
 *      find_link(word)  - returns a pointer the the link containing word <--Added by MT
 *      word_delete(str) - removes item containing string from table <-- Added by MT
 *          
 */

static LINK table[ARRAY_SIZE];  /* table with an entry for each letter */
static LINK *current_link;      /* for list traversal */
static int current_letter;      /* for list traversal */
static LINK *prev;              /* used in find_link, aids with insert & delete */

/*
 *	void init_table()
 *		purpose: set up a LINK array with pointers; each element contains
 *               a pointer to a linked list storing words for each letter
 * input/output: none
 *       errors: none
 *		 method: set the pointers in each of ARRAY_SIZE elements in table[] to NULL
 *
 * Modified by Matthew Thomas
 */
void init_table()
{
	int i;
	
	for(i = 0; i < ARRAY_SIZE; i++)
	{
		table[i].word = NULL;
		table[i].next = NULL;
	}	
}

/*
 *	int in_table(char str[])
 *      purpose: see if a word is in the table
 *        input: str, the word to look for in the table[]
 *      returns: YES if is, NO if not
 *       method: look for word in table, based on the first letter of string;
 *               use a linear search in the letter's linked list; assume list is
 *               sorted so exit early when you reach word that comes after "str"
 *
 *  Modified by Matthew Thomas
 *  Calls on find_link() to find whether the link exists in the table. If not,
 *  find_link() returns NULL. See find_link() comments for more on how it works.
 */
int in_table( char str[] )
{
	return ( find_link(str) == NULL ) ? NO : YES;
}

/*
 * int insert(str, val)
 *		purpose: add an entry to the table
 *		returns: NO if no more memory, YES if OK
 *       errors: malloc fails to find memory to store "str" and the LINK in; prints
 *               message stderr. This is done in the new_link() function.
 *		 method: Inserts new link in linked list pointed to by table[] that stores all
 *               words beginning with the same first letter. Inserts new link in sorted
 *               order.
 *
 * Modified by Matthew Thomas
 * Calls on new_link() to handle malloc() for the word and the LINK memory, as well as
 * initializing the new link with appropriate values. If new_link() fails, return NO
 * immediately.
 *
 * If new_link() succeeds, insert the link by calling find_link() to update static LINK
 * variable "prev". This helps to keep linked list maintained with inserts between
 * existing elements or at the end of the list (empty, or with elements).
 */
int insert( char str[], int val )
{
	//malloc and initialze a new LINK with str and val
	LINK *newlink = new_link(str, val);
	
	if(newlink == NULL)
	{
		fprintf(stderr,"wordfreq: not enough memory to insert new link\n");
		return NO;
	}
	
	//Call on find_link() to update static prev variable and linkp
	LINK *linkp = find_link(str);

	//If prev points to a LINK, insert newlink between elements
	if(prev->next != NULL)
	{
		newlink->next = prev->next;
		prev->next = newlink;
	}
	//Otherwise, insert newlink at the end of the list (either empty or containing links)
	else
	{
		newlink->next = linkp;
		prev->next = newlink;
	}

	return YES;
}

/*
 *	int lookup( str )
 *		purpose: lookup the value associated with str
 *		 method: linear search; stops after reaching post-asciibetical element;
 *               done with find_link()
 *		returns: value in the table associated with "str".  If not there, returns 0
 *
 *  Modified by Matthew Thomas
 *  Calls on find_link() to find whether the link exists in the table and returns
 *  a pointer to it so you can return its value.
 */
int lookup( char str[] )
{
	LINK *linkp = find_link(str);
	return (linkp == NULL) ? NO : linkp->value;
}

/*
 * 	int update( str, val )
 *		purpose: change an entry
 *		 method: search for str and update its value (done via find_link())
 *		returns: YES if found, NO if not
 *
 *  Modified by Matthew Thomas
 *  Calls on find_link() to return a pointer to the entry you want to update.
 *  If it is found, update the value and return YES. Otherwise, return NO.
 */
int update( char str[], int val )
{
	LINK *linkp = find_link(str);
	
	if(linkp)
	{
		linkp->value = val;  //update value in link containing "str"
		return YES;
	}
	
	return NO;	
}

/*
 *	char *firstword()
 *		purpose: returns the first word in the table
 *		returns: NULL if no words in table, otherwise the word
 *
 *  Modified by Matthew Thomas
 *  Check each element in table[] to see if a word exists for that letter. If one is
 *  found, assign current_link and current_letter tracking variables to the first result
 *  and return to nextword().
 */
char *firstword()
{
	int i;
	current_link = NULL;  //initialize static file-scope variable
	
	
	//go through each dummy LINK in table[] until you find one that points to a list
	for(i = 0; i < ARRAY_SIZE; i++)
	{
		//if there is one LINK pointed to by table[i] (i.e. 'a' words)
		if(table[i].next != NULL)
		{
			current_link = table[i].next;
			current_letter = i;
			break;
		}
	}

	return nextword();
}

/*
 *	char *nextword()
 *		purpose: returns ptr to next word in table
 *		returns: ptr to word or NULL if no word there
 *
 *  Modified by Matthew Thomas
 *  Check each element in table[] to see if another word exists for that letter. If one is
 *  found, assign current_link and current_letter tracking variables and return to
 *  nextword(). If not, move on to check the next letter (i.e. next element in table[])
 *  and check.
 */
char *nextword()
{
	if (current_link == NULL)
	{
		return NULL;
	}
	
	char *current_word = current_link->word;
	
	//When NULL, attempt to continue to next "letter" element in table[]
	if (current_link->next == NULL)
	{
		//Find next table[] element with an associated linked list
		while(++current_letter < ARRAY_SIZE)
		{
			//Found a next linked list, update variables 
			if(table[current_letter].next != NULL)
			{
				current_link = table[current_letter].next;
				break;
			}
		}
		
		//reached the end of the table[]
		if (current_letter == ARRAY_SIZE)
		{
			current_link = NULL;
			return current_word;
		}
	}
	//Move to the next LINK in the current "letter" linked list
	else
	{
		current_link = current_link->next;
	}
	
	return current_word;
}

/*
 *	LINK *find_link(char *word)
 *		purpose: find the link in the table that contains the word passed in
 *		  input: the word to look for
 *       errors: 
 *      returns: a pointer to the link containing "word". If not found, NULL.
 *       method: starts search in linked list pointed to in table[] that corresponds
 *               to the first letter of "word". Performs a linear search in that linked
 *               list until it finds the word, or finds a word that comes after it
 *               'asciibetically'. We assume the linked list is sorted, so it stops the
 *               search and returns NULL in that case.
 */
LINK * find_link(char *word)
{
	//Simple check to make sure word being passed in starts with a lowercase letter
	if(word[0] < 'a' || word[0] > 'z')
	{
		//If not, print error and exit, to prevent overflow
		fprintf(stderr,"wordfreq: word must begin with a lowercase letter:\t%s\n", word);
		exit(2);
	}

	prev = &table[word[0] - 'a'];  //updates/initializes the static file variable
	LINK *linkp = prev->next;      //local function pointer to find desired link
	
	//Iterate through the linked list containing words with the first char of "word"
	while(linkp)
	{
		//We found the word, return the pointer to its LINK
		if(strcmp(linkp->word, word) == 0)
		{
			return linkp;
		}
		//When compare > 0, we've passed where word should be when sorted, so stop looking
		else if (strcmp(linkp->word, word) > 0)
		{
			break;
		}

		//Update pointers to check next link
		prev = linkp;
		linkp = linkp->next;
	}

	return NULL;
}

/*
 *	void word_delete(char word[])
 *		purpose: removes the LINK struct containing "str" from the table of linked lists
 *		returns: void
 *       method: calls on find_link() to return a pointer to the LINK attempting to be
 *               removed; NULL if it doesn't exist. If found, update link pointers and
 *               then free memory for the "word" and the LINK struct.
 *        error: if word not found (i.e. find_link() returns NULL), print word to stderr
 */
void word_delete(char word[])
{
	LINK *linkp = find_link(word);
	
	//Found the LINK containing the word to delete. Update pointers and free memory
	if(linkp)
	{
		prev->next = linkp->next;
		free(linkp->word);
		free(linkp);
	}
	else
	{
		fprintf(stderr,"wordfreq: word not found:\t%s\n", word);
	}

	return;
}