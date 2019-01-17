#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

/*
 *	wordlist table module version 4
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
 *	data structure for this unit: dynamically resized array of structs
 */

static int expand_table();
struct entry {
		char *word;		/* the string		*/
		int  value;		/* the count		*/
	};

#define	DEBUG
#define	CHUNKSIZE	3

static struct entry	*table = NULL;		/* pointer to array	*/
static int		table_len = 0;		/* space in array	*/
static int		n_rows;			/* how many in table	*/
static int		current_row;		/* for table traversal	*/

/*
 *	init_table
 */

int expand_table();
void
init_table()
{
	n_rows = 0;
	table = NULL;
	table_len = 0;
}

/*
 *	int in_table(char str[])
 */

int in_table( char str[] )
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

	if ( n_rows == table_len )
		if ( expand_table() == NO )
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


/*
 * expand_table - increase size of table by one CHUNK size amount
 * return NO on malloc/realloc error
 */

static int
expand_table()
{
	table_len += CHUNKSIZE;
#ifdef	DEBUG
	fprintf(stdout,"expanding table to %d entries\n", table_len);
#endif
	table = (struct entry *) realloc(table, table_len*sizeof(struct entry));
	if ( table == NULL )
		return NO;
	else
		return YES;
}
