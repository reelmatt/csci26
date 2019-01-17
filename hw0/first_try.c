#include <stdio.h>
/*
 * reverse a list of numbers
 * 
 * Matthew Thomas -- matthew_thomas@hms.harvard.edu
 */

#define N 10

int main()
{
    float a[N];
    int i;
    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++) {
      scanf("%f", &a[i]);
    }
    printf("Here are your numbers in reverse order\n");
    for(i = N-1; i >= 0; i--) {
      printf(" %f", a[i]);
    }

    putchar('\n');
    return 0;
}
