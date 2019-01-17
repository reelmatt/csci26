#include	<stdio.h>
#include	<string.h>
#include	"wl.h"

/*
 *	wordlist table module version 1
 *
 *	functions are:
 *			init_table()	- set up this module
 *			in_table(str)	- sees if word is in table
 *			insert(str,val) - insert value into table
 *			lookup(str)	- retrieve value
 *			update(str,val) - update value in table
 *			firstword()	- return first word in table
 *			nextword()	- return next word in table
 */

/*
 *	data structure for this unit: two arrays
 *		an array of ints for the counts
 *		an array of arrays of chars for the words
 */

#define	MAXROWS		5		/* room in tables	*/
#define	WLEN		45		/* longest word		*/

static int	value[MAXROWS];			/* frequency of word[i] */
static char	word[MAXROWS][WLEN+1];		/* the strings		*/
static int	n_rows;				/* how many in table	*/
static int	current_row;			/* for table traversal	*/

/*
 *	init_table
 *		purpose: set up filing system 
 *		input:  = output: = errors: =  none
 *		method:  set n_rows to 0
 */

void
init_table()
{
	n_rows = 0;
}

/*
 *	int in_table(char str[])
 *		purpose:  see if a word is in the table
 *		input:    str, a string
 *		  rets:	  YES if is, NO if not
 *		errors:	  none
 *		method:	  look for word in table, use a linear search
 */

int
in_table( char str[] )
{
	int	i = 0;

	while( i<n_rows )
		if ( strcmp( word[i++], str ) == 0 )
			return YES ;
	return NO;
}

/*
 *	int insert(str, val)
 *		purpose: add an entry to the table
 *		returns: NO if no more memory, YES if OK
 *		 method: copy string into last slot, load value, too
 */

int
insert( char str[], int val )
{
	if ( n_rows == MAXROWS || strlen( str ) > WLEN )
		return NO;
	strcpy( word[n_rows], str );		/* insert word	*/
	value[n_rows++] = val ;			/* and its value  */
	return YES;
}

/*
 *	int lookup( str )
 *		purpose: lookup the value associated with str
 *		method:  linear search
 *		returns: value in the table.  If not there, returns 0
 */

int
lookup( char str[] )
{
	int	pos ;

	for( pos = 0 ; pos<n_rows ; pos++ )		/* loop thru tab */
		if ( strcmp( word[pos], str ) == 0 )	/* if found	 */
			return value[pos];		/* ret value     */
	return 0;					/* not found     */
}

/*
 * 	int update( str, val )
 *		purpose: change an entry
 *		method:  search for str and update its value
 *		returns: YES if found, NO if not
 */

int
update( char str[], int val )
{
	int	pos;

	for( pos = 0 ; pos<n_rows ; pos++ )		/* loop 	*/
		if ( strcmp( word[pos], str ) == 0 ){	/* found?	*/
			value[pos] = val ;		/* update	*/
			return YES ;			/* and go	*/
		}
	return NO;
}

/*
 *	char *firstword()
 *		purpose: returns the first word in the table
 *		returns: NULL if no words in table, otherwise the word
 */

char *
firstword()
{
	current_row = 0;
	return nextword();
}

/*
 *	char *nextword()
 *		purpose: returns ptr to next word in table
 *		returns: ptr to word or NULL if no word there
 */

char *
nextword()
{
	if ( current_row >= n_rows )
		return NULL;
	return word[current_row++];
}
