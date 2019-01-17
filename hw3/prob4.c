#include <stdio.h>

/*
 * Code copied from homework assignment. Lines 23 and 27
 * commented out. Last printf statement added for part 4e.
 */

int main()
{
    char n[4][10] = { "ann", "bob", "carol", "dave" };
    char *p1, *p2;
    p1 = n[2];
    p2 = n + 2;

    printf("n is %lu, n[0] is %lu, n[0][0] is %lu\n",
	   (unsigned long)n, (unsigned long)n[0], (unsigned long)n[0][0]);
    printf("(n+1) is %lu, (n+1)[0] is %lu, (n+1)[0][0] is %lu\n",
	   (unsigned long)(n+1), (unsigned long)(n+1)[0],
	   (unsigned long)(n+1)[0][0]);
    printf("p1 is %lu, p1[0] is %lu\n",
	   (unsigned long)p1, (unsigned long)p1[0]);
    /* compiler error:
       "subscripted value is not an array, pointer, or vector" */
    //printf("p1[0][0] is %lu\n", (unsigned long)p1[0][0]);
    printf("p2 is %lu, p2[0] is %lu\n", (unsigned long)p2, (unsigned long)p2[0]);
    /* compiler error:
       "subscripted value is not an array, pointer, or vector" */
    //printf("p2[0][0] is %lu\n", (unsigned long)p2[0][0]);

    //Added printf for question 4e
    printf("p2+1 is %lu\n", (unsigned long)p2+1);

    return 0;
}
