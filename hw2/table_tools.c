#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * table_tools.c
 * 
 * An assortment of tools to help with processing lines and cells when
 * converting table text to HTML tables. To be compiled with tt2ht1.c,
 * tt2ht2.c, and tt2ht3.c for homework 2.
 *
 * find_start() - find first non-whitespace, but still valid, char
 *   put_cell() - wraps cell contents with <td> tags with any attributes
 * valid_char() - checks for EOF, new line, carriage return, and null
 * which_mode() - gets a line and checks to see if it matches a opening tag
 */

#define LINESIZE 512
#define MAXCELL 50
#define NUMATTRIBUTES 10
#define STYLELEN 50

int find_start(int pos, char row[LINESIZE]);
void put_cell(int flag, char cell[MAXCELL], char style[STYLELEN]);
int valid_char(char);
int which_mode(char line[LINESIZE]);

/*
 * find_start()
 * 
 * Ignores leading whitespace to return position where first char appears.
 * If it runs into an invalid char (see valid_char() comments), then it returns
 * last position it encountered.
 * 
 * args:
 *     --int pos: current position in string to process from
 *     --char row: current row from input data to process
 * return:
 *     --position where the first non-whitespace character appears
 */
int find_start(int pos, char row[LINESIZE])
{
	while(pos < LINESIZE && isspace(row[pos]) && valid_char(row[pos]))
	{
		pos++;
	}
	
	return pos;
}

/*
 * put_cell()
 * 
 * This function takes the current cell data and prints it with surrounding <td>
 * tags, and, when present, attributes to place in the opening <td> tag. If the cell
 * exceeds the number of attributes read in, it prints with no attribute.
 *
 * args:
 *     --int has_attribute: 0 if an attribute wasn't read; 1 if a row exists in style[]
 *     --char cell[]: string to be placed in <td></td> tags
 *     --char style[]: attribute, if any, to be place in opening <td> tag
 */
void put_cell(int has_attribute, char cell[MAXCELL], char style[STYLELEN])
{
	if(has_attribute && strlen(style) > 0)
	{
		printf("\n\t\t<td %s>", style);
	}
	else
	{
		printf("\n\t\t<td>");
	}
	
	printf("%s</td>", cell);
	return;
}

/*
 * valid_char()
 *
 * Similar to the function of isspace() from ctype.h, but doesn't check spaces and
 * tabs; only evaluates for end of line/file chars like new line, carriage return,
 * and null. This is useful when processing a row for whitespace, but you want to
 * tell if you've reached the end of what you should be processing.
 *
 * args:
 *     --char c: the character to evaluate
 * return:
 *     --When EOF, new line, carriage return, or null, return 0. Otherwise, return 1.
 *     [isspace() would return 1 for all these cases (except EOF)]
 */
int valid_char(char c)
{
	if(c != '\n' && c != '\r' && c != '\0' && c != EOF)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * which_mode()
 * 
 * args:
 *     --char line[]: current line to evaluate mode
 * return:
 *     --End of input, return 0
 *     --Opening <noprocess> tag present, return 1
 *     --Opening <attributes> tag present, return 2
 *     --Start of a <delim key=value /> tag present, return 3
 *           --used in tt2ht3.c only
 *     --Closing </noprocess> tag present, return -1
 *     --Closing </attributes> tag present, return -2
 *     --Otherwise, defaults mode of table text, return 4
 */
int which_mode(char line[LINESIZE])
{
	while(fgets(line, LINESIZE, stdin) != 0)
	{
		line[strlen(line) - 1] = '\0';    //trim off newline
		char *ret = strchr(line, '<');    //look for tag

		if(ret != '\0' && strcmp(ret, "<noprocess>\0") == 0)
			return 1;
		else if(ret != '\0' && strcmp(ret, "<attributes>\0") == 0)
			return 2;
		else if(ret != '\0' && strncmp(ret, "<delim", 6) == 0)
			return 3;
		else if(ret != '\0' && strcmp(ret, "</noprocess>\0") == 0)
			return -1;
		else if(ret != '\0' && strcmp(ret, "</attributes>\0") == 0)
			return -2;
		else
			return 4;
	}
	
	return 0;
}