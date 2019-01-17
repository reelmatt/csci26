#include <stdio.h>
#include <string.h>

/*
 * strrev.c
 * 
 * purpose: reverses a string in place by calling strrev()
 *          done with two different versions:
 *     1) Array version: treats arguments as arrays (indexing)
 *     2) Pointer version: treats arguments as pointers
 */

char *strrev_arrays(char *s);
char *strrev_pointers(char *s);

/*
 * Initilaizes demonstration strings, prints original value
 * and then the reversed value.
 */
int main()
{
    char example_array1[] = "Hello";
    char example_array2[] = "hi there you";
    char example_pointer1[] = "Hello";
    char example_pointer2[] = "hi there you";

    printf("example1 =\t%s\n", example_array1);
    printf("reverse (arrays) =\t%s\n", strrev_arrays(example_array1));
    printf("reverse (pointers) =\t%s\n", strrev_pointers(example_pointer1));

    printf("example2 =\t%s\n", example_array2);
    printf("reverse (arrays) =\t%s\n", strrev_arrays(example_array2));
    printf("reverse (pointers) =\t%s\n", strrev_pointers(example_pointer2));

    return 0;
}

/*
 * Array version
 *
 * Uses indexing to reverse the string in place. Keeps track
 * of start and end positions. When the start position crosses
 * the end position, you have processed half the string and can
 * return.
 * 
 * args: char *s -- the string to reverse in place
 * returns: pointer to the original string passed in
 */
char *strrev_arrays(char *s)
{
    int start = 0;            //beginning of the string
    int end = strlen(s) - 1;  //end of string, before null terminator

    //have the start & end postions converge, until they cross at the half
    for(start = 0; start <= end; start++, end--)
    {
        char temp = s[start];  //remember the start char
        s[start] = s[end];
        s[end] = temp;
    }
    
    return s;
}

/*
 * Pointer version
 *
 * Uses pointers to reverse the string in place. Keeps track
 * of the start and end positions.  When the start position crosses
 * the end position, you have processed half the string and can return.
 *
 * args: char *s -- the string to reverse in place
 * returns: pointer to the original string passed in 
 */
char *strrev_pointers(char *s)
{
    char *sp = s;                   //pointer to start
    char *ep = s + (strlen(s) - 1); //pointer to end (before null terminator)
    
    //When the pointers cross, you've reached the halfway point and can return
    while(sp <= ep)
    {
        char temp = *sp;  //remember the start char
        *sp = *ep;
        *ep = temp;
        sp++;
        ep--;
    }
    return s;
}
