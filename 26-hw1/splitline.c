#include	<stdio.h>

/*
 * splitline.c
 *
 *    purpose: show one way of splitting a line of text into subsections
 *      input: lines of semicolon-separated data
 *     output: list format of same data
 *     method: split a line of chars into an array of lines of chars
 *
 *      shows: strings, arrays, functions, loops, 
 *
 * 	Try setting these values to short values and exceed the limits to see
 *
 *	a) how C organizes memory
 *	b) how C doesn't care if you do dumb things
 *	c) why error checking is not just something you talk about
 */

#define	LINELEN		200
#define	MAXFIELDS	10
#define	MAXFLDLEN	40

#define	DELIM		';'

int
split_line( char orig[], char fields[MAXFIELDS][MAXFLDLEN] )
/*
 * purpose: parse a line of DELIM-separated items into an array of strings
 *    args: a line of DELIM-separted items and an array of char arrays
 *  method: loop through orig copying and copy to target array.  Change
 *          to next row at each DELIM
 * returns: number of fields found in line
 *    note: no error checking.  See what you can do to break it
 */
{
	int	src_pos,		/* position in source array	*/
		cur_fld,		/* item in fields[] array	*/
		dest_pos;		/* position in dest array	*/

	src_pos = cur_fld = dest_pos = 0;

	while( 1 )
	{
		/* 
		 * if end of record, then terminate current string
		 * and advance to next row in fields[] table
		 */

		if ( orig[src_pos] == DELIM || orig[src_pos] == '\0' )
		{
			fields[cur_fld][dest_pos] = '\0';
			if ( orig[src_pos] == '\0' )
				break;
			cur_fld++;		/* need to check for overflow*/
			dest_pos = 0;
		}
		else

		/*
		 * not end of record, so copy the char from the source
		 * to the current char position in the current string
		 */
		{
			fields[cur_fld][dest_pos] = orig[src_pos];
			dest_pos++;
		}
		src_pos++;
	}
	return cur_fld+1;
}
