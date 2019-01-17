#include <stdio.h>

/* prob2.c
 *
 * Copied from homework assignment. Value and location code
 * added by Matthew Thomas
 */

char t[3] = "hi";

int main(void)
{
	int x, y[4] = { 71, 181, 30, 131 };
	char a[30] = "pointers store addresses.";
	int *q;
	char *p, *s;
	int **r;

	p = a + 4;
	q = &y[0];
	s = &x;
	*s = '0';
	x = 44;
	r = &q;
	*q = q[2] + --x;

	/* write code here to print out values and locations
	   of all vars */

	//Values
	printf("value of t = %s\n", t);
	printf("value of x = %d\n", x);
	printf("value of y[0] = %d\ty[1] = %d\t y[2] = %d\ty[3] = %d\n",
	       y[0], y[1], y[2], y[3]);
	printf("value of a = %s\n", a);
	printf("value of *q = %d\n", *q);
	printf("value of *p = %d\n", *p);
	printf("value of *s = %d\n", *s);
	printf("value of *rr = %d\n", **r);

	//Locations
	printf("location of t = %p\n", &t);
	printf("location of x = %p\n", &x);
	printf("location of y = %p\n", &y);
	printf("location of a = %p\n", &a);
	printf("location of q = %p\n", &q);
	printf("location of s = %p\n", &s);
	printf("location of p = %p\n", &p);
	printf("location of r = %p\n", &r);

	return 0;
}
