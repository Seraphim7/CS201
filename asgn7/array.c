
/* ***********************************************************
 Name: array.c
 Desc: Initialzies, manipulates, and finds largest value in a
        2-d array.

	Students will analyze with gprof and improve code.

  Modified by Alex Novitchkov

************************************************************* */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int largest(int x, int y) {
	if (x>y)
		return x;
	else
		return y;
}

int findLargest(int a[][SIZE]) {
	int largeNum=a[0][0];
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
			largeNum = largest(largeNum, a[x][y]);	
	return largeNum;
}

void doubleVals(int a[][SIZE]) {
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
			a[x][y] = a[x][y]*2;	
}

void initialize(int a[][SIZE]) {

  /* Only works with arrays with size being an even number */
  for (int x = 0; x < SIZE; x++)
  {
    for (int y = 0; y < SIZE; y+=2)
    {
      a[x][y] = x - y;

      if (y != SIZE - 2)
      {
        a[x][y + 1] = x - y - 1;
      }
    }
  }
}

int main() {
	static int a[SIZE][SIZE];
	int large;

	initialize(a);
	doubleVals(a);
	large = findLargest(a);	
	printf("%d\n",large); 

	return 0;
}
