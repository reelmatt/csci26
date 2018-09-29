#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * hello_large.c
 * purpose: convert a string of digits to a number with commas
 *   input: user-typed text string
 *  output: number outputed to console with embedded commas
 *
 * get_a_positive_number() and is_all_digits() functions copied from hello6.c
 * modified slightly for hw1, by Matthew Thomas
 */

#define STRSIZE 100

int get_a_number(char []);
int is_all_digits(char []);
void embed_commas(char [], int);

int main()
{
    char inputstr[STRSIZE];
    int digits = get_a_number(inputstr);
    embed_commas(inputstr, digits);
    return 0;
}

/*
 * code copied from hello6.c sample from class
 * modified by Matthew Thomas
 *
 * purpose: prompt user to enter a positive number
 *  return: number of digits that the user entered
 *          str modifies inputstr from main().
 */
int get_a_number(char str[STRSIZE])
{
    int num_digits = -1;

    while(num_digits <= 0)
    {
        printf("Number? ");
        fgets(str, STRSIZE, stdin);
        num_digits = is_all_digits(str);

        if(num_digits == 0)
        {
            printf("This is not a positive number. Please try again!\n");
        }
    }

    return num_digits;
}

/*
 * code copied from hello6.c sample from class
 * slightly modified by Matthew Thomas to account
 * for cases where no chars are passed through.
 *
 * return: number of digits in str, retrieved from position
 *         the count leaves off at
 */
int is_all_digits(char str[STRSIZE])
{
    int pos = 0;

    while(str[pos] != '\n')
    {
        if( !isdigit(str[pos]) )
        {
            return 0;
        }

        pos++;
    }

    return (pos == 0) ? 1 : pos;
}

/*
 * purpose: takes a string comprising of numbers and adds commas
 *   input: char [] consisting of only numbers
 *  output: print to stdout number formatted with commas
 *    note: (digits - i) % 3 is shorthand to let us know at what
 *          position in the number we are --  e.g. in a five digit
 *          number like 37,463, the number "7" is at i = 1.
 *          (5 - 1) % 3 == 1 and signifies it is the place to put a ','.
 */
void embed_commas(char str[STRSIZE], int digits)
{
    int i;       //counter variable

    for(i = 0; i < digits; i++)
    {
        putchar(str[i]);
        
        /* if we're not at the last digit 
         * AND
         * the current location in the number is 1 before
         * a group of 3 (location % 3 == 1)
         * THEN
         * put a comma in the output
         */
        if((i != (digits - 1)) && ((digits - i) % 3) == 1)
        {
            putchar(',');
        }
    }

    putchar('\n');
}
