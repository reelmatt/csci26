#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * tt2ht1.c
 *
 * purpose: Convert a table formatted as plain text into an HTML-formatted table
 *   input: rows of data with columns separate by tabs or spaces
 *  output: an HTML-formatted table containing the input
 *
 *    note: See README.txt for a note about how this program handles
 *          blank <tr> rows.
 */

#define LINESIZE 512
#define MAXCELL 50

/* In tt2ht1.c */
void process_row(char [LINESIZE]);

/* Linked from table_tools.c */
int find_start(int pos, char row[LINESIZE]);
int valid_char(char);

/*
 * main() prints opening and closing table tags with new lines.
 * When going through input data, it encloses each row with <tr>
 * tags and kicks out to process_row() for formatting each cell.
 */
int main(void)
{
    char line[LINESIZE];

    printf("<table border=1 cellpadding=2>");
    while(fgets(line, LINESIZE, stdin) != 0)
    {
        line[strlen(line) - 1] = '\0';    //trim off newline

        printf("\n\t<tr>");
        process_row(line);
        printf("\n\t</tr>");
    }
    printf("\n</table>\n");

    return 0;
}

/*
 * process_row()
 *
 * Separates a row of input data into whitespace-delimited cells.
 * Calls on find_start() to ignore whitespace, then stores the chars
 * before the next whitespace/end of line (with help of valid_char()).
 * It then encloses each cell with appropriate formatting and <td> tags.
 *
 * args:
 *     --char row[]: current row from input data to process
 */
void process_row(char row[LINESIZE])
{
    char cell[MAXCELL];    //string to store contents of a single cell of data
    int pos = 0;           //keep track of current position in line input
    char c = row[pos];     //store the current char to evaluate

    //Stop if pos is past the maximum LINESIZE, or char is not valid
    //Will loop through however many cells contained in a row
    while(pos < LINESIZE && valid_char(c))
    {
        int cell_pos = 0;

        pos = find_start(pos, row);   //strip off leading whitespace
        c = row[pos];

        //extract a whitespace-delimited cell
        while(pos < LINESIZE && !isspace(c) && valid_char(c))
        {
            cell[cell_pos++] = row[pos++];
            c = row[pos];
        }

        //if chars were passed through to a cell, print it with <td> tags
        if(cell_pos > 0)
        {
            cell[cell_pos] = '\0';
            printf("\n\t\t<td>%s</td>", cell);
        }
    }

    return;
}
