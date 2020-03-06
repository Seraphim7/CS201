
/* ***********************************************************
 Name: sumArray.c
 Desc: Assignment 8 - Sums up array elements numerous times

	Students will modify sumArray routine to improve 
	performance.

 Compile 
	gcc -m32 -std=gnu99 -Wall -g sumArray.c -o sumArray

 Time execution:
	time sumArray

Modified by Alex Novitchkov

************************************************************* */


#include <stdio.h>
#include <stdlib.h>

#define NUM_TIMES 50000
#define ARR_SIZE  100000

static inline double sumArray(register double array[]) {
        register double* end = &array[ARR_SIZE]; /* currently works number % 5 = 0 */

        register double sum=0;

	for (register double* ptr = array; ptr < end; ptr+=5)
        {
	  sum+= *ptr + *(ptr + 1) + *(ptr + 2) + *(ptr + 3) + *(ptr + 4);
        }
        return sum;
}

int main() {
	//print your name
	printf("Alex Novitchkov\n");

	//create and initialize array
	double *array = calloc(ARR_SIZE, sizeof(double));

	array[0]=5;
	array[ARR_SIZE-1]=4;

	//sum up array elements a bunch of times (once is too fast)
	double sum;
	for(int n=0; n<NUM_TIMES; n++) {
		sum=sumArray(array);
	}

	/* print out total to verfiy we processed all entries */
	printf("sum: %lf\n", sum);

	return 1;
}
