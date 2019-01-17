#include	"ws13.h"

/*	some constants */
#define	MAXFLD	40
#define	MAXVAL	120

/*
 *	function declarations fl.c
 *      fatal()         - print error message to stderr then exit
 *      get_delimiter() - updates variables storing command line options
 *      get_file()      - open a file for reading
 *      read_data()     - open a data file and process it
 */
void fatal(char *, char *);
void get_delimiter(char *, char *, char *);
FILE * get_file (char *, char *);
int read_data(char *, FILE *, char, char);

/*
 *	function declarations process.c
 *       process() - read from datafile, format and output selected records
 *     get_table() - allocates memory for name/value pairs
 *    get_record() - reads the next data record from the stream at *fp
 *      get_name() - reads the fieldname from a data file
 *     get_value() - reads the fieldvalue from a data file
 *     get_token() - extracts token from a format file
 *    read_until() - reads chars until specified max, or ending char
 *     mailmerge() - replaces %fieldname% tokens with stored data/system() calls
 *   check_token() - checks which kind of token is found in the format file
 *   run_command() - run a system command
 * replace_token() - replace a token found in a format file

 */
int	process(FILE*, FILE*, char, char);
symtab_t * get_table();
int get_record(symtab_t *, FILE *, char, char);
char * get_name(FILE *fp, char, char);
char * get_value(FILE *fp, char, char);
char * get_token(int, FILE *, char, char);
int read_until(int, char *, int, char, char, char, FILE *);
void mailmerge(symtab_t *, FILE *, char, char);
void check_token(symtab_t *tp, FILE *fmt, char, char);
void run_command(symtab_t *tp, FILE *fmt);
void replace_token(char c, symtab_t *tp, FILE *fmt, char, char);

/*
 *	function declarlations helpers.c
 *    first_char() - strip any leading whitespace from stdin
 *    valid_char() - checks whether the current char is "valid"
 *    new_string() - allocates memory for a new word string to store in a LINK
 *  char_advance() - advances to first char of the next field to read
 */ 
int first_char(FILE *fp);
int valid_char(int);
char * new_string(int);
void char_advance(int, char, FILE *);
