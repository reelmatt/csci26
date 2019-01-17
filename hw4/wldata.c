#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wl.h"
#include "wl_mods.h"

/*
 *	wldata.c
 *
 *  code inspired from lecture 7 samples, modularity example presented by Bruce.
 *  modifications made by Matthew Thomas
 *
 *	functions are:
 *      new_link(str, val) - allocates memory for a LINK struct and assigns values
 *		new_string(str)    - allocates memory for a new word string to store in a LINK
 *		cp_string(str)     - allocates memory for a new word string to store in a LINK
 */
 
/*
 * new_link()
 *
 *      purpose: allocates memory for a LINK struct and assigns values
 *        input: str and val, to insert into the LINK
 *      returns: pointer to the LINK that's created; NULL if not enough memory
 *       errors: if malloc() fails to assign memory, output error message to stderr,
 *               free any memory that was allocated, and return NULL
 *       method: Uses malloc() to allocate enough memory for a LINK. Calls on new_string
 *               to allocate memory for the word stored in "str". Assigns the values and
 *               then returns the pointer to its location.
 */
LINK * new_link(char *str, int val)
{
	LINK *newlink;
	
	if( (newlink = malloc(sizeof(LINK))) != NULL )     //malloc for LINK
	{
		if( (newlink->word = cp_string(str)) != NULL ) //malloc for word
		{
			//All mallocs passed; initialize link
			newlink->value = val;
			newlink->next = NULL;
			return newlink;
		}
	}
	
	//One or more mallocs failed; free any memory that was reserved and return
	fprintf(stderr,"wordfreq: not enough memory to insert new link\n");
	free(newlink->word);
	free(newlink);
	
	return NULL;
}

/*
 * new_string()
 *
 *      purpose: allocates memory for a new word string to store in a LINK
 *        input: str, the word to allocate memory for (for insert into a LINK)
 *      returns: pointer to the string that's created; NULL if not enough memory
 *       method: Uses malloc() to allocate enough memory to hold "str". Frees memory if
 *               fails.
 */
char * new_string()
{
	char *newstr = malloc(BUFLEN);
	
	//Get memory for str and check
	if (newstr == NULL)
	{
		fprintf(stderr,"wordfreq: not enough memory to create new string\n");
		free(newstr);
		return NULL;
	}
	
	return newstr;
}

/*
 * cp_string()
 *
 *      purpose: allocates memory for a new word string to store in a LINK
 *        input: str, the word to allocate memory for (for insert into a LINK)
 *      returns: pointer to the string that's created; NULL if not enough memory
 *       method: Uses malloc() to allocate enough memory to hold "str". Frees memory if
 *               fails.
 */

char * cp_string(char *str)
{
	char *newstr;
	
	//Get memory for str and check
	newstr = malloc( 1 + strlen( str ) );
	if (newstr == NULL)
	{
		free(newstr);
		return NULL;
	}	
	strcpy( newstr, str );
	
	return newstr;
}