#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * tt2ht1.c
 * 
 * purpose: Convert a table formatted as plain text into an HTML-formatted table
 *   input: rows of data with columns separate by tabs or spaces
 *  output: an HTML-formatted table containing the input
 */
 
#define LINESIZE 512
#define MAXCELL 50

int process_row(char [LINESIZE]);
void put_cell(char [MAXCELL], int);

int main(void)
{
	char line[LINESIZE];
	
	//printf("Start main\n");
	while(fgets(line, LINESIZE, stdin) != 0)
	{
		printf("<tr>");
		process_row(line);
		printf("\n</tr>\n\n");
	}

	return 0;
}

int process_row(char row[LINESIZE])
{
	//printf("Start process_row()\n\n");
	char cell[MAXCELL];
	int pos = 0;
	int cols = 0;  //keep track of how many columns
	
	while(pos < LINESIZE && row[pos] != '\n')  //iterate through each char in the line
	{
		//printf("Start row\n");
		int cell_pos = 0;
		
		while(pos < LINESIZE && isspace(row[pos]))
		{
			pos++;
		}
		
		//printf("pos = %d, cell_pos = %d, char = %c\n", pos, cell_pos, row[pos]);
		while(pos < LINESIZE && !isspace(row[pos]))  //iterate until you reach white space
		{
//			printf("pos = %d, cell_pos = %d, char = %c\n", pos, cell_pos, row[pos]);
			cell[cell_pos++] = row[pos++];
		}
		
		//printf("Post cell\n");
		if(cell_pos > 0)
		{
			put_cell(cell, cell_pos);
			//cell[cell_pos] = '\0';
			//cols++;
			// printf("<td>");
// 			fputs(cell, stdout);
// 			printf("</td>");
		}
		
		
	}
	
	return cols;
}

void put_cell(char cell[MAXCELL], int length)
{
	char start[9] = "\n\t<td>\0"
	char end[6] = "</td>\0"
	//printf("in put_cell()\n\n");
	//printf("cell == %s", cell);
	cell[length] = '\0';
//	printf("\n\t<td>");
	fputs(start, stdout);
	fputs(cell, stdout);
	fputs(end, stdout);
//	printf("</td>");
}