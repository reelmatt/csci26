#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

/*
 *	wordlist table module version 3
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
 *	data structure for this unit: one array of structs
 */

struct entry {
		int  value;		/* the count		*/
		char *word;		/* the string		*/
	};

#define	MAXROWS		25		/* room in tables	*/

static struct entry	table[MAXROWS];		/* the array of structs */
static int		n_rows;			/* how many in table	*/
static int		current_row;		/* for table traversal	*/

/*
 *	init_table
 */

void
init_table()
{
	n_rows = 0;
}

/*
 *	int in_table(char str[])
 */

int
in_table( char str[] )
{
	int	i = 0;

	while( i<n_rows )
		if ( strcmp( table[i++].word, str ) == 0 )
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
	char	*newstr ;

	if ( n_rows == MAXROWS )
		return NO;

	newstr = malloc( 1 + strlen( str ) );	/* get memory		*/
	if ( newstr == NULL )			/* or die		*/
		return NO;
	strcpy( newstr, str );			/* copy to mem		*/
	table[n_rows].word = newstr ;		/* put ptr in tab 	*/
	table[n_rows++].value = val ;		/* and its value 	*/
	return YES;
}

/*
 *	int lookup( str )
 */
int
lookup( char str[] )
{
	int	pos ;

	for( pos = 0 ; pos<n_rows ; pos++ )		/* loop thru tab */
		if ( strcmp( table[pos].word, str) == 0 ) /* if found	 */
			return table[pos].value;		/* ret value     */
	return 0;					/* not found     */
}

/*
 * 	int update( str, val )
 */

int
update( char str[], int val )
{
	int	pos;

	for( pos = 0 ; pos<n_rows ; pos++ )		/* loop 	*/
		if (strcmp(table[pos].word,str) == 0 ){	/* found?	*/
			table[pos].value = val ;	/* update	*/
			return YES ;			/* and go	*/
		}
	return NO;
}

/*
 *	int firstword()
 */

char *
firstword()
{
	current_row = 0;
	return nextword();
}

/*
 *	char *nextword()
 */

char *
nextword()
{
	if ( current_row >= n_rows )
		return NULL;
	return table[current_row++].word;
}

