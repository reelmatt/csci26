#include <stdio.h>

/* prob3.c
 * 
 * Code copied from homework assignment.
 */

int main()
{
    int m[5] = { 4, 3, 2, 1, 0 };
    int *p;

    p = m + 2;

    printf("m is %lu, &m is %lu, &m[0] is %lu, m[0] is %lu\n",
	   m, (unsigned long)&m, (unsigned long)&m[0], m[0]);
    printf("p is %lu, &p is %lu, &p[0] is %lu, p[0] is %lu\n",
	   p, (unsigned long)&p, (unsigned long)&p[0], p[0]);

    return 0;

}
