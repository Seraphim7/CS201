/*********
*
* Author: Alex Novitchkov
* intfun.c
* CS-201: Assignment 2
*
* THis program tests whether a computer stores its data as little or big endian.*  This program then prints out the sizes of several different datatypes. Finall* y, it displays the integers -3 to 10 in decimal, hex, and bianry.
*
*********/

#include "stdio.h"

/*
Figures out if computer is big endian

@return - returns 0 (false) or 1 (true)
*/
char IsBigEndian();

/*
Prints sizes of some datatypes
*/
void PrintSizeOf();

/*
Prints decimal, hexadecimal, and binary
*/
void DecHexBinaryTable();

/*
Prints -3 to 10 in binary

@param - the decimal number as an int
*/
void PrintAsBinary(int decNumber);

/*----------*/
int main()
{
  printf("\n");

  printf("Author: Alex Novitchkov\n");

  if (IsBigEndian() == 1)
  {
    printf("Computer is big endian\n");
  }
  else
  {
    printf("Computer is little endian\n");
  }

  printf("\n");

  PrintSizeOf();

  printf("\n");

  DecHexBinaryTable();

  return 1;
}

/*----------*/
char IsBigEndian()
{
  unsigned int data = 0x12345678;
  unsigned int* intPtr = NULL;

  intPtr = &data;
  
  if (*intPtr == 0x78)
  {
    return 1;
  }
  return 0;
}

/*----------*/
void PrintSizeOf()
{
  printf("sizeof(short) = %ld \n", sizeof(short));
  printf("sizeof(int) = %ld \n", sizeof(int));
  printf("sizeof(long) = %ld \n", sizeof(long));
  printf("sizeof(long long) = %ld \n", sizeof(long long));
}

/*----------*/
void DecHexBinaryTable()
{
  printf("Dec     Hex            Binary\n");
  
  for (int i = -3; i <= 10; i++)
  {
    if (i < 0)
    {
      printf("%d", i);
      printf("    ");

     printf("0x%hx", i);
    }
    else if (i > 9)
    {
      printf("%d", i);
      printf("    ");
      printf("0x%04x", i);
    }
    else
    {
      printf(" %d", i);
      printf("    ");
      printf("0x%04x", i);
    }

    printf("    ");
    
    PrintAsBinary(i);

    printf("\n");
  }
}

/*----------*/
void PrintAsBinary(int decNum)
{
  int quotient = decNum;
  int bitNum[16];

   for (int i = 15; i >= 0; i--) /* Common routine for - and + numbers */
   {
     if (i < 4 && i >= 0)
     {
        bitNum[i] = 0;
     }
     else
     {
       bitNum[i] = quotient % 2;

       if (quotient == 1)
       {
         quotient = 0;
       }

       quotient = quotient / 2;
     }
   }

  if (decNum < 0) /* If decNum is negative */
  {
     for (int i = 15; i >= 0; i--) /* Flip the bits */
     {
       if (bitNum[i] == -1)
       {
         bitNum[i] = 0;
       }
       else if (bitNum[i] == 0)
       {
         bitNum[i] = 1;
       }
     }

     int i = 15;
     
     /* Add 1 to bits */
     while (bitNum[i] != 0)
     {
       bitNum[i] = 0;

       i--;
     }
       
     bitNum[i] = 1;
    /*================*/
  }


   for (int i = 0; i < 16; i++) /* Common routine for - and + numbers */
   {
     if (i == 4 || i == 8 || i == 12)
     {
       printf(" ");
     }
    
    if (i == 8)
    {
       printf(" ");
    }

     printf("%d", bitNum[i]);
   }
}
