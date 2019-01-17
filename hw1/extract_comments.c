#include <stdio.h>

/*
 *  extract_comments.c
 *
 * purpose: extracts comments from a C program and writes them out
 *   input: .c file
 *  output: all the comments from the input file
 *   usage: extract_comments < myprog.c
 */

void old_style(int, int);
void new_style(int, int);
void string_mode(int);

int main()
{
    int c, prev;                 //keep track of current and previous char

    /* Iterate through by character until you reach end of file */
    while( (c = getchar()) != EOF)
    {
        if (c == '/')
        {
            prev = c;            //store char as it might be start of comment
            c = getchar();       //get next char to evaluate it

            if (c == '*')
            {
                old_style(c, prev);      //switch to old_style mode
            }
            else if (c == '/')
            {
                new_style(c, prev);      //switch to new_style mode
            }
        }

        if (c == '"')
        {
            string_mode(c = getchar());  //switch to string_mode
        }
    }

    return 0;
}

/*
 * string_mode
 *
 * In this mode, start by checking whether quote char is used for a
 * comparison (e.g. c == '"'). If it is, return immediately.
 *
 * Otherwise, the quote is the beginning of a string, so ignore all
 * comment chars, '/' and '*'. Just read in chars until you find the
 * closing '"' quote. Then return to main().
 */
void string_mode(int c)
{
    //Check if quote is not the start of a string
    if (c == '\'')
    {
        return;
    }
    
    //Selection is a string, so read chars until the closing quote
    while(c != '"' && c != EOF)
    {
        c = getchar();
    }
    
    return;
}


/*
 * new_style mode
 * 
 * In this mode, comments begin with '//' and end with a newline, '\n'.
 * Iterate through chars until we reach the '\n', print the newline char,
 * and kick back to the main loop.
 */
void new_style(int c, int prev)
{
    //put the last two chars, aka, the beginning of the comment
    putchar(prev);
    putchar(c);

    while((c = getchar()) != '\n')
    {
        putchar(c);
    }
    putchar(c);     //c exits the while loop with '\n'. we output and return
    return;
}

/*
 * old_style mode
 *
 * In this mode, comments begin with '/ *' and end with '* /' (no spaces).
 * Iterate through chars (unless we reach EOF) and look for a '*' char
 * followed by a '/' char. If we find them adjacent to each other, break
 * the loop and return to main.
 */
void old_style(int c, int prev)
{
    //put the last two chars, aka, the beginning of the comment
    putchar(prev);
    putchar(c);

    while( (c = getchar()) != EOF)
    {
        putchar(c);

        if(c == '*')            //if a '*', could be last char before end of comment
        {
            c = getchar();      //get next char to evaluate it

            if (c == '/')       //if a '/', that means the end of the comment
            {
                putchar(c);
                putchar('\n');  //add a newline
                break;          //and exit back to main
            }
            else
            {
                putchar(c);     //if not a '/', putchar and continue to the next
            }
        }
    }
    return;
}
