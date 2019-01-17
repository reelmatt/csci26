#include	<stdio.h>
#include	<stdlib.h>
#include	"fl.h"
#include	"ws13.h"

/*
 *	formletter program version 1.0
 *
 *	usage: fl format < datafile
 *
 *	data comes from stdin, output goes to stdout
 */

static char	*myname ;		/* used by fatal() */

/*
 * main()
 *
 * Goes through command line arguments to identify options,
 * one format file (always the first non-option listed), and
 * 'n' number of data files listed (or stdin, if none).
 *
 * Options can change the field and record delimiters from defaults
 * of ';' and '\n' respectively. fatal() is called, via get_file() if
 * a file cannot be opened. If no files are listed, fatal() is also called.
 */
int main(int ac, char *av[])
{
	FILE *format = NULL;
	myname = *av;

    int i = 0;
	int any_files = NO;
	char field_delim = ';';
	char record_delim = '\n';
	
	while (++i < ac)
	{
		if(av[i][0] == '-')
			get_delimiter(&field_delim, &record_delim, av[i]);
		else if(!format)
			format = get_file(av[i], "format file");
		else
			any_files = read_data(av[i], format, field_delim, record_delim);
    }
	
	if(!format)
		fatal("usage: fl format [datafile..]", "");
	else if(!any_files)
		process(format, stdin, field_delim, record_delim);

	fclose(format);
	return 0;
}

/*
 *	fatal error handler
 *	purpose: print error message to stderr then exit
 *	input:   two strings that are printed 
 *	never returns
 */
void fatal(char *s1, char *s2)
{
	fprintf(stderr, "%s: %s%s\n",  myname, s1, s2 );
	exit(1);
}

/*
 * get_delimiter(field, record, option)
 *
 * Purpose: updates variables storing command line options
 *   Input: field, variable to hold field separator
 *          record, variable to hold record separator
 *          option, the command line argument passed through
 *  Return: None. This function passes through addresses of variables
 *          storing separator values. get_delimiter() updates the correct
 *          one.
 * Options: -r: changes record separator. Char following 'r' is the separator
 *          -R: changes record separator to newline (returns to default)
 *          -d: changes field separator. Char following 'd' is the separator
 *          -D: changes field separator to newline
 *    Note: the -R option is not specified in the homework assignment. I figured
 *          this would be nice to have for the same reason -D is included.
 */
void get_delimiter(char * field, char * record, char * option)
{
	if (option[1] == 'R')
		*record = '\n';
	else if(option [1] == 'r')
		*record = option[2];
	else if(option [1] == 'D')
		*field = '\n';
	else
		*field = option[2];

	return;
}

/*
 * get_file(file, type)
 *
 * Purpose: open a file for reading
 *   Input: file, name of the file
 *          type, "data file" or "format file" (to help with error messages)
 *  Return: pointer to the file that was opened
 *  Method: factors out error-checking for cases where file fails to open. Calls
 *          fatal() with an appropriate error message (with aid of char * type) to
 *          exit the program.
 */
FILE * get_file (char * file, char * type)
{
	FILE *fp;

	if((fp = fopen(file, "r")) == NULL)
		fatal("file error: cannot open ", type);
	
	return fp;
}

/*
 * read_data()
 *
 * Purpose: open a data file and process it
 *   Input: name, name of file to open
 *          format, format file to merge with
 *          field, separator char for field
 *          record, separator char for record
 * Returns: YES, on successfully reading a file
 *  Errors: get_file() will call fatal() if file cannot be opened
 *          process() will return fatal() if there's an error while processing
 */
int read_data(char *name, FILE *format, char field, char record)
{
	FILE *data = get_file(name, "data file");
	process(format, data, field, record);
	
	return YES;
}
