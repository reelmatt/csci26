#include <stdio.h>
#include <string.h>
/*
 * unit-tests.c
 */

#define LINESIZE 512
#define MAXCELL 50
#define NUMATTRIBUTES 10
#define STYLELEN 50

//table_tools.c 
int find_start(int pos, char row[LINESIZE]);
void put_cell(int flag, char cell[MAXCELL], char style[NUMATTRIBUTES]);
int valid_char(char);
int which_mode(char line[LINESIZE]);

/*//tt2ht3.c
void noprocess_mode(char [LINESIZE]);
int attribute_mode(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN]);
char delim_mode(char [LINESIZE]);
void process_row(char [LINESIZE], char[NUMATTRIBUTES][STYLELEN], int, char);
void get_cell(char [LINESIZE], char [MAXCELL], int, char);
*/
//unit-tests.c
void find_start_test();
void valid_char_test();
void put_cell_test();
void which_mode_test();
void no_process_test();
void attribute_test();
void delim_test();
void process_row_test();
void get_cell_test();

int main(void)
{
	find_start_test();
	put_cell_test();
	valid_char_test();
	which_mode_test();
	
	no_process_test();
//	attribute_test();
//	delim_test();
//	process_row_test();
//	get_cell_test();
}

void find_start_test()
{
	printf("\nFIND START\n----------\n");

	char start[5][50];
	strcpy(start[0], "hello world\n");
	strcpy(start[1], "\t\t  \t hello world\t  \n");
	strcpy(start[2], "\n");
	strcpy(start[3], "\t");
	strcpy(start[4], "");

	printf("Expecting: |pos 0|\n");
	printf("Expecting: |pos 6|\n");
	printf("Expecting: |pos 0|\n");
	printf("Expecting: |pos 1|\n");
	printf("Expecting: |pos 0|\n");
	
	int i;
	for(i = 0; i < 5; i++)
	{
		printf("Results: |pos %d|\n", find_start(0, start[i]));
	}
	
}

void valid_char_test()
{
	printf("\nVALID CHAR\n----------\n");
	
	printf("Testing 'a':\texpecting 1\treturns %d\n", valid_char('a'));
	printf("Testing '1':\texpecting 1\treturns %d\n", valid_char('1'));
	printf("Testing '\\n':\texpecting 0\treturns %d\n", valid_char('\n'));
	printf("Testing '\\r':\texpecting 0\treturns %d\n", valid_char('\r'));
	printf("Testing '\\0':\texpecting 0\treturns %d\n", valid_char('\0'));
	printf("Testing EOF:\texpecting 0\treturns %d\n", valid_char(EOF));
	
}

void put_cell_test()
{
	printf("\nPUT CELL\n----------\n");
	
	char cell[MAXCELL] = "hello world";
	char blank_cell[MAXCELL] = "\0";
	char style[NUMATTRIBUTES] = "clas='nam'";
	char blank_style[NUMATTRIBUTES] = "\0";
	
	printf("Expecting: '<td>hello world</td>'");
	put_cell(0, cell, style);
	printf("\nExpecting: '<td>hello world</td>'");
	put_cell(0, cell, blank_style);
	printf("\nExpecting: '<td></td>'");
	put_cell(0, blank_cell, style);
	printf("\nExpecting: '<td></td>'");
	put_cell(0, blank_cell, blank_style);

	printf("\nExpecting: '<td class='name'>hello world</td>'");
	put_cell(1, cell, style);
	printf("\nExpecting: '<td>hello world</td>'");
	put_cell(1, cell, blank_style);
	printf("\nExpecting: '<td class='name'></td>'");
	put_cell(1, blank_cell, style);
	printf("\nExpecting: '<td></td>'");
	put_cell(1, blank_cell, blank_style);
}

void which_mode_test()
{
	printf("\nWHICH MODE\n----------\n");
	char line[LINESIZE];
	int mode = which_mode(line);
	int expecting[12] = {1, 1, 1, 2, 3, -1, -2, 4, 4, 4, 4, 0};
	int i;
	for(i = 0; i < 12; i++)
	{
		printf("Testing: |%s|\nexpecting %d\t returns%d\n\n", line, expecting[i], mode);
		mode = which_mode(line);
	}
}

void no_process_test()
{
	char line[LINESIZE];
	printf("\nNO PROCESS MODE\n----------\n");
	printf("Expecting: \n");
	noprocess_mode(line);
	printf("Expecting: \n");
	noprocess_mode(line);
	printf("Expecting: \n");
	noprocess_mode(line);	
}

void attribute_test()
{
	printf("\nATTRIBUTE MODE\n----------\n");
}

void delim_test()
{
	printf("\nDELIM MODE\n----------\n");
}

void process_row_test()
{
	printf("\nPROCESS ROW MODE\n----------\n");
}

void get_cell_test()
{
	printf("\nGET CELL MODE\n----------\n");
}