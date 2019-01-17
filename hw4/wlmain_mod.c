#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	"wl.h"
#include 	<string.h>
#include	"wl_mods.h"

/*
 *	wordlist	main module
 *
 *	program reads words from standard input until EOF
 *	then prints all words it saw with the number of times
 *	each word appeared.  Order is order of appearance.
 *
 *	calls functions in a filer module to store and retrieve
 *	the words.
 *
 *	history: modified 11.11.00 to answer all -Wall warnings
 *
 *  modifications by Matthew Thomas
 *  Adds read_word() to prevent buffer overflow when reading in a word from input file
 */

/*
 *	definitions and declarations are in wl.h
 *  new function definitions are in wl_mods.h -- added by Matthew Thomas
 */

void convert_to_lower_case(char *);

int
main()
{
	char *bufptr, *wordptr;

	/* ... set up word filing module ... */

	init_table();	

	/* ... read words and store them ... */
	
	bufptr = read_word();
	
	while(bufptr != NULL)
	{
		convert_to_lower_case( bufptr );

		if ( in_table( bufptr ) == YES )
			update( bufptr, 1 + lookup( bufptr ) );
		else if ( insert( bufptr, 1 ) == NO ){
			fprintf(stderr,"wordfreq: out of memory\n");
			exit(1);
		}
		bufptr = read_word();
	}

	/* ... move cursor down the table printing out results */

	for( wordptr = firstword() ; wordptr != NULL; wordptr = nextword() )
		printf("%5d\t%s\n", lookup( wordptr ), wordptr );

	return 0;
}

/*
 * char * read_word()
 *
 *   purpose: reads a word from stdin, using whitespace as delimeter
 *     input: stdin
 *   returns: pointer to the "str" that is read; NULL if malloc, realloc fail or no word
 *    errors: if malloc() fails to assign memory, return NULL (error message and free()
 *            occur in new_string() function). If realloc() fails, do the same (error and
 *            free take place here).
 *    method: Calls on new_string() to malloc() space for a BUFLEN size word. Ignores any
 *            leading whitespace and reads chars into the string one at a time, until
 *            EOF or isspace(char). If we've exceeded the size of the string, realloc
 *            space for the current size + another BUFLEN size chunk.
 */
char * read_word()
{
	int wordlen = BUFLEN;
	char *str = new_string();
	
	if (str == NULL)
		return NULL;
	
	char c = first_char();
	int i = 0;             //keeps track if ANY chars were valid/word stored in "str"
	
	//once you get to the start of an actual word, read in chars 1 at a time
	while(valid_char(c))
	{
		str[i++] = c;      //Store char in "str"
		c = fgetc(stdin);  //Get next char
		
		//if you've gone past currently allocated size, attempt to realloc
		if(i >= wordlen)
		{
			wordlen += BUFLEN;  //add another BUFLEN size chunk to the total length

			if((str = realloc(str, wordlen)) == NULL)
			{
				fprintf(stderr, "wordfreq: could not realloc enough memory\n");
				free(str);
				return NULL;
			}
		}
	}
	
	return (i == 0) ? NULL : str;
}

/*
 * int valid_char(char c)
 *
 *  purpose: checks whether the current char is "valid"
 *    input: a char
 *   errors: none
 *  returns: YES if char is valid (i.e. not the EOF or whitespace); NO otherwise
 */
int valid_char(char c)
{
	if (c != EOF && !isspace(c))
		return YES;
	
	return NO;
}

/*
 * char first_char()
 *
 *  purpose: strip any leading whitespace from stdin
 *    input: stdin
 *   errors: none
 *  returns: the first non-whitespace char; EOF for no data in stdin; whitespace for
 *           cases where no non-whitespace chars are present.
 */
char first_char()
{
	char c = fgetc(stdin);
	
	//ignore any leading whitespace (e.g. newlines)
	while(isspace(c) && c != EOF)
	{
		c = fgetc(stdin);
	}
	
	return c;
}

/*
 * this function converts any string to all lower-case
 * letters.  Right now it is not being used since
 * the script that calls this program converts the text
 * anyway.
 */

void
convert_to_lower_case( char *str )
{
	while( *str )
	{
		*str = tolower( (int) *str );
		str++;
	}
}
