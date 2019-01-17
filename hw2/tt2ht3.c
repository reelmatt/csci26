#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * tt2ht3.c
 *
 *     purpose: Convert a table formatted as plain text into an
 *              HTML-formatted table
 *       input: Accepts plain text, column attributes, and text table data
 *              as inputs. A <delim /> tag indicates how to convert text
 *              table data.
 *      output: an HTML-formatted table containing the input
 *
 * Nested tags: see README.txt for discussion of how tt2ht3.c (and tt2ht2.c) handles
 *              overlapping sections and ill-formated text.
 *        Note: See README.txt for a note about how this program handles
 *              blank <tr> rows.
 */

#define LINESIZE 512
#define MAXCELL 50
#define NUMATTRIBUTES 10
#define STYLELEN 50

/* In tt2ht3.c */
void noprocess_mode(char [LINESIZE]);
int attribute_mode(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN]);
char delim_mode(char [LINESIZE]);
void process_row(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN], int, char);
void get_cell(char [LINESIZE], char [MAXCELL], int, char);

/* Linked from table_tools.c */
int find_start(int pos, char row[LINESIZE]);
void put_cell(int flag, char cell[MAXCELL], char style[STYLELEN]);
int valid_char(char);
int which_mode(char line[LINESIZE]);

/*
 * main()
 *
 * This works as a FSM, checking the current line to see if it matches a
 * mode and passing off to the corresponding function based on input. It
 * accepts four forms of input:
 *     1) <noprocess> mode, which just outputs lines as-is
 *     2) <attributes> mode, which stores each line in a 2d array
 *     3) <delim key=value /> mode, which specifies a delimiter to use
 *     4) text table data, handled by process_row() to convert to an HTML table
 */
int main(void)
{
    char line[LINESIZE];                  //array to store current line
    char styles[NUMATTRIBUTES][STYLELEN]; //2d array for attributes, one per row
    int num_attributes = 0;               //number of attributes found
    char delim;
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
            case 3:
                delim = delim_mode(line);
                break;
            case -1:
            case -2:
                break;    //closing tags without openings
            default:
                printf("\t<tr>");
                process_row(line, styles, num_attributes, delim);
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
 * same code as appears in tt2ht2.c
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
 * copied from tt2ht2.c;
 * modified to ignore rogue <delim> tags when storing styles; delimit based on newline
 *
 * When in this mode, store each line (including blank lines) in the styles 2d array.
 * It calls on which_mode() to check if it has reached EOF or a closing </attributes>
 * tag, and returns the number of attributes found. If it encounters rogue <noprocess>
 * tags, it discards them (by calling on get_cell() to store a blank entry in the
 * styles array). For rows with attributes, it calls on find_start() to trim any leading
 * whitespace. get_cell() then extracts the attribute found.
 *
 * note: this version fixes the bug in tt2ht2.c that would delimit attributes based on
 *       whitespace. tt2ht3.c can pass a specified delimiter to get_cell(), and I chose
 *       to use '\n' as the delimiter here. This allows attributes like,
 *               "class='name here' id='user'"
 *       that include whitespace. However, if there is _trailing_ whitespace, this version
 *       will include that in the attribute.
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
        char cell[MAXCELL];     //string to store cell data in

        //ignore rogue <noprocess> and <delim /> tags appearing in attribute_mode
        if(mode == 1 || mode == 3)
        {
            //pass in a null string and a null delimiter
            get_cell("\0", cell, 0, '\0');
        }
        else
        {
            //start at beginning of row to find start pos
            int pos = find_start(0, row);

            get_cell(row, cell, pos, '\n');
        }
        strcpy(styles[attributes++], cell);

        mode = which_mode(row);
    }

    return attributes;
}

/*
 * delim_mode()
 *
 * Checks for a properly formatted delimiter tag <delim value=X /> where
 * "X" is the chosen delimiter. If the closing "/>" does not appear in the
 * row, the input is ignored and a null char is stored instead.
 *
 * args:
 *     --char row[]: current row from input data to process
 */
char delim_mode(char row[LINESIZE])
{
    char *target = strchr(row, '=');

    //check for proper tag ending
    if(strstr(target, "/>") != 0)
    {
        return target[1];  //return the char after '='
    }
    else
    {
        return '\0';
    }
}

/*
 * process_row()
 *
 * copied from tt2ht2.c;
 * modified to accept a user-specified delimiter
 *
 * Separates a row of input data into user-specified delimited cells (defaults
 * to whitespace-delimited). Calls on find_start() to ignore leading whitespace,
 * then stores the chars before the next delimiter/end of line by calling on
 * get_cell(). It then encloses each cell with appropriate tags, formatting,
 * and <td> tags by calling on put_cell().
 *
 * note: if a user specifies a delimiter, leading and trailing whitespace will
 *       be included in the cell.
 *
 * args:
 *     --char row[]: current row from input data to process
 *     --styles[][]: 2d array of attributes from which to populate <td> tags
 *     --int attributes: number of attributes found in input data
 *     --char delim: user-specified delimiter; defaults to NULL if not set
 */
void process_row(char row[LINESIZE], char styles[NUMATTRIBUTES][STYLELEN],
				 int attributes, char delim)
{
    char cell[MAXCELL];    //string to store contents of a single cell of data
    int pos = 0;           //keep track of current position in line input
    int cols = 0;          //keep track of number of columns found
    char c = row[pos];     //store the current char to evaluate

    //Stop if pos is past the maximum LINESIZE, or char is newline or EOF
    //Will loop through however many cells contained in a row
    while(pos < LINESIZE && valid_char(c))
    {
        //if a user-specified delimiter is present
        if(delim != '\0')
        {
            get_cell(row, cell, pos, delim);
        }
        //default whitespace delimited
        else
        {
            pos = find_start(pos, row);      //strip off leading whitespace
            get_cell(row, cell, pos, '\0');  //delimits at next whitespace
        }

        pos += strlen(cell);     //update position based on length of cell found

        //if not an empty cell, output it and update cols
        if(strlen(cell) > 0)
        {
            //checks if current col exceeds attributes found in input
            int has_attribute = cols < attributes;

            put_cell(has_attribute, cell, styles[cols]);
            cols++;
        }

        //if the stored char is the delimiter, skip to the next char
        c = (row[pos] == delim) ? row[++pos] : row[pos];
    }

    return;
}

/*
 * get_cell()
 *
 * copied from tt2ht2.c;
 * modified to accept a user-specified delimiter
 *
 * Given a starting position in a row, store all chars into a cell
 * until reaching the MAXCELL size or delimiter (if specified; whitespace
 * by default), and while it is a valid_char().
 *
 * args:
 *     --char row[]: current row from input data to process
 *     --char cell[]: string from parent function to store cell data
 *     --int pos: current position in input row to evaluate
 */
void get_cell(char row[LINESIZE], char cell[MAXCELL], int pos, char delim)
{
    int cell_pos = 0;
    char c = row[pos];

    while(cell_pos < MAXCELL && valid_char(c))
    {
        cell[cell_pos++] = row[pos++];
        c = row[pos];

        //if no delimiter is present, and char is whitespace, break
        if(delim == '\0' && isspace(c) && c != EOF)
        {
            break;
        }
        //when delimiter is present, check if current char matches
        else if(valid_char(c) && c == delim)
        {
            break;
        }
    }

    cell[cell_pos] = '\0';  //terminate string; null string if cell_pos == 0
    return;
}
