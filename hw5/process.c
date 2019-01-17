#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<string.h>
#include	"fl.h"
#include	"ws13.h"

/**
 *	process(fmt, data)
 *
 *	Purpose: read from datafile, format and output selected records
 *	Input:       fmt - input stream from format file
 *		        data - stream from datafile
 *         end_field - char delimiter for end of field (default: ';')
 *        end_record - char delimiter for end of record (default: '\n')
 *	Output:  copied fmt to stdout with insertions
 *	Errors:  not reported, functions call fatal() and die
 *	history: 2012-11-28 added free_table (10q BW)
 *           2018-11-16 modified by Matthew Thomas for hw5
 *  method:  Allocates memory for a table to store fieldname and fieldvalue
 *           pairs. This uses the ws13 storage system and functions. Then, it
 *           stores these value pairs for each record -- get_record() -- and
 *           fills in the format file with matching results -- mailmerge(). It
 *           iterates through each record found in a given data file, then
 *           clears the ws13-style storage table, frees memory, closes the data
 *           file, and returns.
 **/
int process(FILE *fmt, FILE *data, char end_field, char end_record)
{
	symtab_t *table = get_table(); 	        //allocate memory for storage table

	while ( get_record(table, data, end_field, end_record) != NO )  
	{
		if(firstword(table))                               /* ignore blank lines */
		{
			mailmerge(table, fmt, end_field, end_record);  /* merge with format */
			clear_table(table);                            /* discard data */		
		}	
	}

	free_table(table);                        /* no memory leaks! */
	fclose(data);                             /* close data file  */
	return 0;
}

/*
 * get_table()
 *
 * Purpose: allocates memory for wordstore table for fieldname/fieldvalue pairs
 *   Input: none
 *  return: pointer to symtab_t if allocation successful
 *          NULL if allocation not successful, and call to fatal() to exit program
 */
symtab_t * get_table ()
{
	symtab_t *tp;

	if ( (tp = new_table()) == NULL )
		fatal("Cannot create storage object","");
	
	return tp;
}

/*
 * get_record(tp, fp)
 *
 * Purpose: reads the next data record from the stream at *fp
 *   Input: tp, from wordstore package; where to store data read in
 *          fp, file to read record from
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Return: YES, on successfully storing a full record
 *          NO, on end of file
 *  Method: Reads chars until the end of current record (or EOF). Calls
 *          helper functions to read in a fieldname and fieldvalue according
 *          to various size (MAXFLD and MAXVAL) constraints, and delimiters
 *          (end_field and end_record). It then inserts the strings into the
 *          storage system.
 */
int get_record(symtab_t *tp, FILE *fp, char end_field, char end_record)
{
	int c = fgetc(fp);

	//while we haven't reached the end of a record/file yet
	while(c != EOF && c != end_record)
	{
		char *name, *val;  //pointers to use for insert()
		
		//put the first char back as it might be part of fieldname
		ungetc(c, fp);
		
		//read one field, store strings in pointer variables
		name = get_name(fp, end_field, end_record);
		val = get_value(fp, end_field, end_record);
		
		//insert it into the symtable
		insert(tp, name, val);     

		//try a next field
		c = fgetc(fp);
	}

	return (c == end_record) ? YES : NO;
}

/*
 * get_name(fp)
 *
 * Purpose: reads the fieldname from a data file
 *   Input: fp, data file to read a fieldname from record
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Return: char * to malloc'd memory storing fieldname
 *          fatal() when malloc (via new_string()) fails
 *  Errors: empty field name, calls fatal()
 *          no terminating '=', searched for via char_advance() 
 *  Method: Allocates storage for a MAXFLD size string. It then reads in
 *          chars until specified ending-constraints. It error-checks to
 *          ensure valid input.
 */
char * get_name(FILE * fp, char end_field, char end_record)
{
	//calls fatal() if malloc fails
	char *str = new_string(MAXFLD);

	//strip leading whitespace
	int c = first_char(fp);
	
	//add to string, and get the last char read
	c = read_until(c, str, (MAXFLD - 1), '=', end_field, end_record, fp);
	
	//error check to see if last char is what is should be
	if(strlen(str) == 0)
		fatal("invalid data: ", "fieldname is blank");
	else if(c != '=')
		char_advance(c, '=', fp);
	
	return str;
}

/*
 * get_value(fp)
 *
 * Purpose: reads the fieldvalue from a data file
 *   Input: fp, file to read a fieldvalue from a record
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Errors: none
 *  Return: char * to malloc'd memory storing fieldname
 *          fatal() when malloc (via new_string()) fails 
 *  Method: Like get_name(), allocates storage for a MAXVAL size string. Reads
 *          chars until specified ending-constraints. It then ensures appropriate
 *          char is passed back to get_record().
 */
char * get_value(FILE * fp, char end_field, char end_record)
{
	//calls fatal() if malloc fails
	char *str = new_string(MAXVAL);
	
	//add to string, and get the last char read
	int c = fgetc(fp);
	c = read_until(c, str, (MAXVAL - 1), EOF, end_field, end_record, fp);

	//error check to see if last char is what is should be
	if(c == end_record)
		ungetc(c, fp);
	else if(c != end_field)
		char_advance(c, end_field, fp);
		
	return str;
}

/*
 * get_token(fp)
 *
 * Purpose: extracts token from a format file
 *   Input: c, the first char of the token
 *          fmt, data file to read a fieldname from record
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Errors: missing closing %, i.e. unterminated fieldname in format file
 *  Return: char * to malloc'd memory storing token
 *          fatal() when malloc (via new_string()) fails 
 *  Method: Allocates storage for a MAXFLD size string, same as a fieldname size
 *          in data files. Reads chars until specified ending-constraints. It
 *          advances to next % if any.
 *    Note: if a %fieldname% is not properly terminated, the remaining %token%'s
 *          will be printed to stdout. The fatal() call is made at EOF, so
 *          intermediate %token% values are printed. In this case, no data should
 *          be replaced (unless there's a matching error in the data file).
 */
char * get_token(int c, FILE * fp, char end_field, char end_record)
{
	//calls fatal() if malloc fails	
	char *str = new_string(MAXFLD);

	//add to string, and get the last char read
	c = read_until(c, str, (MAXFLD - 1), '%', end_field, end_record, fp);
	
	//error check to see if last char is what is should be
	if (c != '%')
		char_advance(c, '%', fp);
		
	return str;
}

/*
 * read_until(c, str, max, end_fld, end_rec, fp)
 *
 * Purpose: reads chars until specified max, or ending char
 *   Input: c, starting char to evaluate
 *          str, string to add chars to
 *          max, maximum size the string allows
 *          end_fld, delimiter for fields
 *          end_rec, delimiter for records (can be same as end_fld)
 *          fp, file to read chars from
 *  Return: the last char that was read 
 */
int read_until(int c, char *str, int max, char special, char end_fld, char end_rec, FILE *fp)
{
	int i;
	
	//read up to max chars
	for(i = 0; i < max; i++)
	{
		//if EOF or an ending char - break, terminate string, and return
		if( c == EOF || c == special || c == end_fld || c == end_rec)
		{
			break;
		}
		//otherwise, add to the string, and check the next char
		else
		{
			str[i] = c;
			c = fgetc(fp);
		}
	}
	str[i] = '\0';

	return c;
}

/*
 * mailmerge(tp, fmt)
 *
 * Purpose: called for each record in a given data file; replaces %fieldname% tokens
 *          in a format file with stored values from a data file (or system() calls
 *          when token is of form %!command%)
 *   Input: tp, pointer to table containing all name=value pairs
 *          fmt, pointer to file containing tokens to be replaced
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Method: Check every char in the format file. If it is a '%', check to see if it
 *          is a token, and call the appropriate function. If not, then just output
 *          as-is. fseek() returns to the start of the doc so it can be re-used for
 *          a new record.
 */
void mailmerge(symtab_t *tp, FILE *fmt, char end_field, char end_record)
{	
	int c;
	
	while( (c = fgetc(fmt)) != EOF)
	{
		if(c == '%')
			check_token(tp, fmt, end_field, end_record);  //does this match a %-case?
		else
			fputc(c, stdout);      //just output char
	}

	fseek(fmt, 0L, SEEK_SET);      //copied from assignment spec
	return;
}

/*
 * check_token(tp, fmt)
 *
 * Purpose: checks which kind of token is found in the format file
 * options: %%, print out a single %
 *          %!, start of a command, call on system() via run_command()
 *          %fieldname%, potentially replaced with a stored fieldvalue for
 *                  corresponding fieldname
 *   Input: tp, pointer to table containing all name=value pairs
 *          fmt, pointer to file containing tokens to be replaced
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 */
void check_token(symtab_t *tp, FILE *fmt, char end_field, char end_record)
{
	int c = fgetc(fmt);
		
	if(c == '%')
		fputc(c, stdout);          //double %, print out one %
	else if(c == '!')
		run_command(tp, fmt);      //command syntax
	else
		replace_token(c, tp, fmt, end_field, end_record); //regular token to replace
}

/*
 * run_command(tp, fmt)
 *
 * Purpose: run a system command
 *   Input: tp, pointer to table containing all name=value pairs
 *          fmt, pointer to file containing tokens to be replaced
 *  Method: When a '%!' has been found in a format file, a system command should be run.
 *          get_token() is called to extract the command, followed by several functions.
 *    Note: shell commands are limited to MAXFLD in length, i.e. they are extracted as
 *          fieldname token values, so the same limitation is put in place. For longer
 *          commands, combine into a shell script and call that via a command.
 */
void run_command(symtab_t *tp, FILE *fmt)
{
	char *token = get_token(fgetc(fmt), fmt, '%', '%');  //%s are not used
	
	//following commands copied from homework spec for how to call shell commands
	table_export(tp);
	fflush(stdout);
	system(token);

}

/*
 * replace_token(c, tp, fmt)
 *
 * Purpose: replace a token found in a format file
 *   Input: c, first char of token
 *          tp, pointer to table containing all name=value pairs
 *          fmt, pointer to file containing tokens to be replaced 
 *          end_field, char indicating end of field (default: ';')
 *          end_record, char indicating end of a record (default: '\n')
 *  Method: get_token() retrieves the token string from the format file.
 *          lookup() sees if a corresponding fieldvalue exists for the given
 *          fieldname. If a value exists, it is output.
 */
void replace_token(char c, symtab_t *tp, FILE *fmt, char end_field, char end_record)
{
	char *token = get_token(c, fmt, end_field, end_record);
	char *replacement = lookup(tp, token);

	if(replacement != NULL)
	{
		fputs(replacement, stdout);	
	}
	
	return;
}