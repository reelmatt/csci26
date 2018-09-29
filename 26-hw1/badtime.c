#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * badtime.c
 * purpose: find lines with incorrect time info
 *   input: sched datafile
 *  output: print lines with bad time info
 * 
 * compile: use with splitline.c, unmodified version used
 *          in class. copied from ~lib113
 *  assume: time data in sched file appears as "TI=xx:xx"
 *          badtime.c will find incorrect hours (not in
 *          range of 0-24), and incorrect minutes (not
 *          in range of 0-59).
 */

#define LINESIZE 512
#define MAXFIELDS 10
#define MAXFLDLEN 40
#define NUM_SCHED_FIELDS 6
#define TAGLEN 3
#define TIMELEN 8

int wrong_time(char [TIMELEN]);
int split_line(char [], char [MAXFIELDS][MAXFLDLEN]);
void get_time(char[MAXFIELDS][MAXFLDLEN], char[TIMELEN]);

/*
 * badtime.c
 *     --reads data in from sched file
 *     --uses split_line() to separate each train line
 *       into a 2d array with each key=value in a row
 *     --get_time() extracts only the time info ("TI=...")
 *     --wrong_time() evaluates the time portion
 */
int main()
{
    char line[LINESIZE];
    char data[MAXFIELDS][MAXFLDLEN];
    char time[TIMELEN];

    while(fgets(line, LINESIZE, stdin) != 0)
    {
        line[strlen(line) - 1] = '\0'; /*trim off newline */

        //call split_line to separate one row into a 2d array
        if (split_line(line, data) == NUM_SCHED_FIELDS)
        {
            //retrive "TI=xx:xx" data and store in "time"
            get_time(data, time);

            //if there's an error, wrong time will return 1
            //print the offending line and a newline
            if(wrong_time(time) == 1)
            {
                fputs(line, stdout);
                printf("\n");
            }
        }       
    }
    return 0;
}

/*
 * get_time()
 *    --accepts a 2d array, train[][], of all key=value pairs for a single
 *      train in sched file
 *    --accepts a char array, train_time[], declared in main() to pass back
 *      the time information to be used later
 */
void get_time(char train[MAXFIELDS][MAXFLDLEN], char train_time[TIMELEN])
{
    int row;
    char tag[TAGLEN] = "TI=";

    //go through each row in 2d array looking for "TI="
    for(row = 0; row < NUM_SCHED_FIELDS; row++)
    {
        if(strncmp(tag, train[row], TAGLEN) == 0)
        {
            //copy into train_time, passed through from main()
            strcpy(train_time, train[row]);
        }
    }
    return;
}

/*
 * wrong_time()
 *    --returns 0 if correct time (no errors)
 *    --returns 1 if incorrect time
 *    --accepts a char array, time[], with data like "TI=xx:xx"
 *    --starts at position TAGLEN and iterates through TIMELEN.
 *      At each digit, it checks whether the char at that position
 *      is allowed. Cases 3 and 4 are hours, case 5 should be the ':',
 *      and cases 6 and 7 are the minute positions.
 */
int wrong_time(char time[TIMELEN])
{
    int i;            //counter
    int badtime = 0;  //0 for no errors, 1 for errors
    char check;       //variable to store current char

    for(i = TAGLEN; i < TIMELEN; i++)
    {
        check = time[i];
        switch(i)
            {
                //digit #1 of hours, can only be 0-2
                case 3:
                    if(check < '0' || check > '2')
                    {
                        badtime = 1;
                    }
                    break;
                //digit #2 of hours, can only be 0-9
                case 4:
                    if(check < '0' || check > '9')
                    {
                        badtime = 1;
                    }
                    //if the 1st digit was a '2', 2nd digit can
                    //must be 0-4
                    if(time[i - 1] == '2' && check > '4')
                    {
                        badtime = 1;
                    }
                    break;
                //A ':' must appear after two hour digits
                case 5:
                    if(check != ':')
                    {
                        badtime = 1;
                    }
                    break;
                //digit #1 of minutes, can only be 0-5
                case 6:
                    if(check < '0' || check > '5')
                    {
                        badtime = 1;
                    }
                    break;
                //digit #2 of minutes, can only be 0-9
                case 7:
                    if(check < '0' || check > '9')
                    {
                        badtime = 1;
                    }
                    break;
                default:
                    badtime = 0;
            }
        //If there was an error at any position, break out
        //of for loop
        if(badtime == 1)
        {
            break;
        }
    }
    return badtime;
}
