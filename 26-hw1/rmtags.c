#include <stdio.h>

/*
 *   rmtags.c
 *  purpose: remove tags but leave semicolons from text file
 *    input: text
 *   output: text with semicolons, but no tags
 *    usage: rmtags < sched
 */

#define TAG 1
#define NOT_TAG 2

int main()
{
    int c;           //store the current char
    int mode = TAG;  //start in TAG mode

    //Iterate through each char until the end of file
    while( (c = getchar()) != EOF )
    {
        /* If in TAG mode, move on to next char. If c is
           an '=', we've reached the end of the tag, so
           switch modes. */
        if ( mode == TAG )
        {
            if( c == '=')
            {
                mode = NOT_TAG;
            }
        }
        /* If in NOT_TAG mode, putchar() and then check
           if we've reached the start of a new tag.
           Either a ';', '\n', or '\t' char. */
        else if (mode == NOT_TAG)
        {
            putchar(c);
	  
            if( c == ';' || c == '\n' || c == '\t' )
            {
                mode = TAG;
            }
        }
    }

    return 0;
}
