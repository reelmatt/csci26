#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>

/*
 *  hello6.c
 *
 *	purpose: shows how to examine a string char by char
 *
 *      Copied from course code, week 2
 *      Modified for hw1 by Matthew Thomas
 *          repeat_a_message() --> while loop
 *          is_all_digits()    --> for loop
 */

#define STRSIZE 100

void repeat_a_message(char [], int);
int  get_a_positive_number();

int main()
{
	int	maxnum;             /* limit */
	char message[STRSIZE];	/* an array of chars */
    
	printf("Print what string? ");
	fgets(message, STRSIZE, stdin);	/* read in a string	*/

	maxnum = get_a_positive_number();
	repeat_a_message( message, maxnum );

	return 0;
}

/* purpose: prints out the string in `message' for `times' iterations */
void repeat_a_message( char message[STRSIZE], int times )
{
    int i = 0;	                         // local variable

    while(i < times)
	{
	    printf( "%d. %s", i, message);   // print it
	    i++;
    }
}

int
get_a_positive_number()
/*
 * purpose: demand a positive integer from the user
 * returns: a positive integer
 */
{
	int inputval = -1;
	char inputstr[STRSIZE];
	int is_all_digits(char []);

	while( inputval <= 0 )
	{
		printf("Repeat it how many times? ");	/* prompt	*/
		fgets(inputstr, STRSIZE, stdin );	/* input	*/
		if ( is_all_digits( inputstr ) == 0 )	    /* digits?	*/
			printf("This is not a number: %s", inputstr );
		else {
			inputval = atoi( inputstr );
			if ( inputval <= 0 )
				printf("%d is not positive number\n", inputval);
		}
	}
	return inputval;	/* send value back to caller */
}

/*
 * purpose: examine a string and see if all the chars are digits
 * returns: 1 if all chars before the newline are digits, 0 otherwise
 *
 * modified behavior for when no chars are entered
 * --class file had returned 1; it now checks for a blank entry and returns 0
 */
int is_all_digits( char str[STRSIZE] )
{
    int pos;

    for(pos = 0; pos < STRSIZE; pos++)
    {
        if(str[pos] == '\n')
        {
            break;
        }
        
        if(!isdigit(str[pos]))
        {
            return 0;
        }
    }
    
    //if pos==0, there were no chars so return 0
    //otherwise, no problems, return 1
    return (pos == 0) ? 0 : 1;
}

