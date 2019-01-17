#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * tt2ht2.c
 *
 * purpose: Convert a table formatted as plain text into an HTML-formatted table
 *   input: rows of data with columns separate by tabs or spaces
 *			Accepts plain text, column attributes, and text table data as inputs.
 *  output: an HTML-formatted table containing the input
 *
 * Nested tags: see README.txt for discussion of how tt2ht2.c (and tt2ht3.c) handles
 *              overlapping sections and ill-formated text.
 *        Note: See README.txt for a note about how this program handles
 *              blank <tr> rows.
 */

#define LINESIZE 512
#define MAXCELL 50
#define NUMATTRIBUTES 10
#define STYLELEN 50

/* In tt2ht2.c */
void noprocess_mode(char [LINESIZE]);
int attribute_mode(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN]);
void process_row(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN], int);
void get_cell(char [LINESIZE], char [MAXCELL], int);

/* Linked from table_tools.c */
int find_start(int pos, char row[LINESIZE]);
void put_cell(int flag, char cell[MAXCELL], char style[STYLELEN]);
int valid_char(char);
int which_mode(char line[LINESIZE]);


/*
 * main()
 *
 * This works as a FSM, checking the current line and passing off to the
 * corresponding mode based on input. It accept three forms of input:
 *     1) <noprocess> mode, which just outputs lines as-is
 *     2) <attributes> mode, which stores each line in a 2d array
 *     3) text table data, handled by process_row() to convert to an HTML table
 */
int main(void)
{
    char line[LINESIZE];
    char styles[NUMATTRIBUTES][STYLELEN];
    int num_attributes = 0;

    int mode = which_mode(line);

    while(mode != 0)
    {
        switch(mode)
        {
            case 1:
                noprocess_mode(line);
                break;
            case 2:
                num_attributes = attribute_mode(line, styles);
                break;
            default:
                printf("\t<tr>");
                process_row(line, styles, num_attributes);
                printf("\n\t</tr>\n");
                break;
        }

        mode = which_mode(line);
    }
    return 0;
}


/*
 * noprocess_mode()
 *
 * Calls on which_mode() to see if it has reached the EOF, or has encountered a
 * closing </noprocess> tag. If you have, break and return back to main. Otherwise,
 * print out each row from the input source.
 *
 * args:
 *     --char row[]: current row from input data to process
 */
void noprocess_mode(char row[LINESIZE])
{
    int mode = which_mode(row);
    while(mode != 0 && mode != -1)
    {
        printf("%s\n", row);
        mode = which_mode(row);
    }

    return;
}

/*
 * attribute_mode()
 *
 * When in this mode, store each line (including blank lines) in the styles 2d array.
 * It calls on which_mode() to check if it has reached EOF or a closing </attributes>
 * tag, and returns the number of attributes found. If it encounters rogue <noprocess>
 * tags, it discards them (by calling on get_cell() to store a blank entry in the
 * styles array). For rows with attributes, it calls on find_start() to trim any leading
 * whitespace. get_cell() then extracts the attribute found.
 *
 * note: this version delimits attributes based on whitespace so a row consisting of
 *       "class='name here'" will be stored as "class='name". tt2ht3.c fixes this bug
 *       as it get_cell distinguishes based on a specified delimiter.
 *
 * args:
 *     --char row[]: current row from input data to process
 *     --char styles[][]: 2d array of strings to store each attribute found
 * returns:
 *     --the number of attributes (rows) found in the input data
 */
int attribute_mode(char row[LINESIZE], char styles[NUMATTRIBUTES][STYLELEN])
{
    int attributes = 0;    //keep track of how many attributes have been found
    int mode = which_mode(row);

    while(attributes < NUMATTRIBUTES && mode != 0 && mode != -2)
    {
        char cell[MAXCELL];            //string to store cell data in

        //ignore rogue <noprocess> tags appearing in attribute_mode
        if(mode == 1)
        {
            //pass in a null string
            get_cell("\0", cell, 0);
        }
        else
        {
            //start at beginning of row to find start pos
            int pos = find_start(0, row);

            get_cell(row, cell, pos);
        }
        strcpy(styles[attributes++], cell);

        mode = which_mode(row);
    }

    return attributes;
}

/*
 * process_row()
 *
 * Separates a row of input data into whitespace-delimited cells.
 * Calls on find_start() to ignore leading whitespace, then stores the chars
 * before the next whitespace/end of line by calling on get_cell(). It then
 * encloses each cell with appropriate tags, formatting, and <td> tags by
 * calling on put_cell().
 *
 * args:
 *     --char row[]: current row from input data to process
 *     --int attributes: number of attributes found in input data
 *     --styles[][]: 2d array of attributes from which to populate <td> tags
 */
void process_row(char row[LINESIZE], char styles[NUMATTRIBUTES][STYLELEN],
				 int attributes)
{
    char cell[MAXCELL];    //string to store contents of a single cell of data
    int pos = 0;           //keep track of current position in line input
    int cols = 0;          //keep track of number of columns found
    char c = row[pos];     //store the current char to evaluate

    //Stop if pos is past the maximum LINESIZE, or char is newline or EOF
    //Will loop through however many cells contained in a row
    while(pos < LINESIZE && valid_char(c))
    {
        pos = find_start(pos, row);   //strip off leading whitespace
        get_cell(row, cell, pos);
        pos += strlen(cell);          //update position based on length of cell found

        //if not an empty cell, output it and update cols
        if(strlen(cell) > 0)
        {
            //checks if current col exceeds attributes found in input
            int has_attribute = cols < attributes;

            put_cell(has_attribute, cell, styles[cols]);
            cols++;
        }

        c = row[pos];
    }

    return;
}

/*
 * get_cell()
 *
 * Given a starting position in a row, store all chars into a cell
 * until reaching the MAXCELL size or whitespace and while it is
 * a valid_char(), meaning not the end of a line or file. (i.e. it
 * negates some of the cases isspace() checks for).
 *
 * args:
 *     --char row[]: current row from input data to process
 *     --char cell[]: string from parent function to store cell data
 *     --int pos: starting position in input row to evaluate
 */
void get_cell(char row[LINESIZE], char cell[MAXCELL], int pos)
{
    int cell_pos = 0;
    char c = row[pos];

    while(cell_pos < MAXCELL && !isspace(c) && valid_char(c))
    {
        cell[cell_pos++] = row[pos++];
        c = row[pos];
    }

    cell[cell_pos] = '\0';  //terminate string; null string if cell_pos == 0
    return;
}
