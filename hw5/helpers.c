#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "ws13.h"
#include "fl.h"

/*
 * new_string()
 *
 *      purpose: allocates memory for a new word string to store in a LINK
 *        input: str, the word to allocate memory for (for insert into a LINK)
 *      returns: pointer to the string that's created; NULL if not enough memory
 *       method: Uses malloc() to allocate enough memory to hold "str". Calls fatal()
 *               if malloc fails, which exits the program
 */
char * new_string(int size)
{
	char *newstr = malloc(size);
	
	//Get memory for newstr and check
	if (newstr == NULL)
		fatal("memory error:", "not enough memory to create new string\n");
	
	return newstr;
}

/*
 * char first_char()
 *
 *  purpose: strip any leading whitespace from stdin
 *    input: FILE pointer
 *   errors: none
 *  returns: the first non-whitespace char; EOF for no data in stdin; whitespace for
 *           cases where no non-whitespace chars are present.
 */
int first_char(FILE *fp)
{
	int c = fgetc(fp);
	
	//ignore any leading whitespace (e.g. newlines)
	while(isspace(c) && c != EOF)
	{
		c = fgetc(fp);
	}
	
	return c;
}

/*
 * int valid_char(char c)
 *
 *  purpose: checks whether the current char is "valid"
 *    input: a char
 *   errors: none
 *  returns: YES if char is valid (i.e. not the EOF or whitespace); NO otherwise
 */
int valid_char(int c)
{
	if(c != EOF && !isspace(c))
		return YES;
		
	return NO;
}

/*
 * char_advance(c, terminator, fp)
 *
 *  purpose: advances to first char of the next field to read
 *    input: c, first char to check
 *           terminator: '=' for fieldname,
 *                       'end_field' for fieldvalue
 *                       '%' for fieldname in format file
 *           fp, pointer to file to get chars from
 *   errors: if reading extra chars of a fieldname, and EOF is reached before
 *           an '=', call fatal() for invalid data.
 *  returns: none
 */
void char_advance(int c, char terminator, FILE *fp)
{	
	while(c != EOF && c != terminator)
		c = fgetc(fp);
	
	if(c == EOF && terminator == '=')
		fatal("invalid data: ", "field does not contain an equals sign");
	else if(c == EOF && terminator == '%')
		fatal("invalid format: ", "missing closing % sign");
	
	return;
}
