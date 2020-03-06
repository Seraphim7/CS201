/*
Author: Alex Novitchkov
CS201 - Assignment 2a

This program takes a float and breaks it into its sign, exponent, and fraction parts
*/

#include "stdio.h"
#include "stdlib.h"

/*
Prints out the hex and decimal versions of a number

@param inputDec - an inputted floating point number
*/

void Print(float inputDec);

/*
Prints out the binary versions of a number

@param inputDec - an inputted floating point number
@param start - the starting point for printing
@param end - the ending point for printing
@param frac - determines whether fractional piece
*/
void PrintBinaryExpFrac(float inputDec, int start, int end, int frac);

/*==========================================*/
int main(int argc, char* argv[])
{
  unsigned int* inputDecPtr = NULL;
  float inputDec;

  printf("\n");
  printf("Author: Alex Novitchkov\n\n");

  if (argc != 2)
  {
    printf("Usage: %s float_value\n", argv[0]);
    return -1;
  }
  
  inputDec = (float) atof(argv[1]);

  inputDecPtr = (unsigned int*) &inputDec;

  printf("Float val:  %f\n", inputDec);
  printf("In hex:     0x%x\n", *inputDecPtr);

 Print(inputDec);
  
  return -1;
}

/*=========================================*/
void Print(float inputDec)
{
   printf("In binary:  ");
   PrintBinaryExpFrac(inputDec, 31, 0, 0);

   unsigned int* inputDecPtr = (unsigned int*) &inputDec;
 
   unsigned int expBits = 0;
   unsigned int fracBits = 0;

   printf("\n\n");

   printf("Sign:         ");
   printf("%d       ", (*inputDecPtr >> 31) & 1);
   printf("0x%x    ", (*inputDecPtr >> 31) & 1);
   printf("%d\n", (*inputDecPtr >> 31) & 1);
   
   expBits = (*inputDecPtr >> 23) & 0xFF; /* Shfiting and clearing */

   printf("Exp bits:   ");
   printf("%3d       ", expBits);
   printf("0x%x   ", expBits);
   PrintBinaryExpFrac(inputDec, 30, 23, 0);

   printf("\n");

   fracBits = *inputDecPtr & 0x7FFFFF; /* Shifting and clearing */

   printf("Frac bits:  ");
   printf("%3d    ", fracBits);
     
   if (fracBits == 0)
   {
     printf("0x%.5x   ", fracBits);
   }
   else
   {
     printf("0x%x   ", fracBits);
   }

   PrintBinaryExpFrac(inputDec, 22, 0, 2); 

   printf("\n");
}

/*==================================*/
void PrintBinaryExpFrac(float inputDec, int start, int end, int frac)
{
  unsigned int* inputDecPtr = NULL;

  inputDecPtr = (unsigned int*) &inputDec;
  
  for (int i = start; i >= end; i--)
  {
    if (frac == 2) /* Offset by 1 space */
    { 
      if (i == start + 1 ||  i == start - 3 || i == start - 11 || i == start - 19)
      {
        printf(" ");
      }
      else if (i == start - 7 || i == start - 15 || i == start - 23)
      {
        printf("  ");
      }
    }
    else
    {
      if (i == start ||  i == start - 4 || i == start - 12 || i == start - 20)
      {
        printf(" ");
      }
      else if (i == start - 8 || i == start - 16 || i == start - 24)
      {
        printf("  ");
      }
    }

     printf("%d", (*inputDecPtr >> i) & 1);
  }
}
