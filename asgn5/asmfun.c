/*
Author: Alex Novitchkov
Assignment 5

First, the program is to calculate the volume of a sphere given a radius
Second, the program is to print out the CPU vendor ID
Third, the program is going to use the quadratic formula to solve an equation
*/

#include "stdio.h"

/*
@param radius - radius of a sphere
@return double - returns the volume of a sphere

Calculates the volume of a sphere based from the radius
*/
double sphereVolume(double radius);

/*
Prints out the CPU vendor ID
*/
void printCpuVendorID();

/*
@param a - The coefficient in the term ax^2
@param b - The coefficient in the term bx
@param c - The coefficient in the term c

Runs the quadratic formula on ax^2+bx+c
*/
void quadraticFormula(double a, double b, double c);

/*------------------------*/
int main()
{
  double volume;
  double a = 3.0;
  double b = 10.0;
  double c = -3.0;

  printf("\n");
  printf("Author: Alex Novitchkov\n");

  volume = sphereVolume(4.5);

  printf("Volume: %f \n", volume);
  printCpuVendorID();
  quadraticFormula(a, b, c);

  return 1;
}

/*--------------------------------------*/
double sphereVolume(double radius)
{
     double volume;
     double numerator = 4.0;
     double denominator = 3.0;

     asm(
           "fldl   %[numerator]   \n"
           "fldl   %[radius]      \n"
           "fmulp                 \n"
           "fldl   %[radius]      \n"
           "fmulp                 \n"
           "fldl   %[radius]      \n"
           "fmulp                 \n"
           "fldpi                 \n"
           "fmulp                 \n"
           "fldl   %[denominator] \n"
           "fdivrp                \n" /* divides ST(0) by ST(1): Reverse */
           "fstpl   %[result]     \n"
           
           :[result] "=m" (volume) /* output (mapping volume to [result] */
           /* input (map radius to radius and denominator to denominator */
           : [radius] "m" (radius),
             [denominator] "m" (denominator),
             [numerator] "m" (numerator)
           :                       /* clobbers (no registers were modified) */
    );

     return volume;
}

/*----------------------------*/
void printCpuVendorID()
{
  char s1[4];
  char s2[4];
  char s3[4];
  int num;

      asm(
           "movl $0x0,%%eax    \n"
           "cpuid              \n"
           "mov %%eax, %[num]  \n"
           "mov %%ebx,%[s1]    \n"
           "mov %%edx,%[s2]    \n"
           "mov %%ecx,%[s3]    \n"
      
           :                        /* No output */
           : [s1]  "m" (s1),        /* three variables as input */
             [s2]  "m" (s2),
             [s3]  "m" (s3),
             [num] "m" (num)
           : "%eax", "%ebx", "%ecx", "%edx"  /* reverting registers */
     );
  
  printf("\n");
  printf("CPU vendor ID: ");
  printf("%d", num);  

  for (int i = 0; i < 4; i++)
  {
    printf("%c", s1[i]);
  }

  for (int i = 0; i < 4; i++)
  {
    printf("%c", s2[i]);
  }

  for (int i = 0; i < 4; i++)
  {
    printf("%c", s3[i]);
  }
  
  printf("\n\n");
}

/*-----------------------------------------*/
void quadraticFormula(double a, double b, double c)
{
  double result;
  double four = 4.0;
  double two = 2.0;

      asm(
         "fldl      %[b]       \n"
         "fldl      %[b]       \n"
         "fmulp                \n"
         "fstpl     %[result]  \n"
         "fldl      %[four]    \n"
         "fldl      %[a]       \n"
         "fmulp                \n"
         "fldl      %[c]       \n"
         "fmulp                \n"
         "fldl      %[result]  \n"
         "fsubp                \n"
         "fsqrt                \n"
         "fldl      %[b]       \n"
         "fsubrp               \n"
         "fstpl     %[result]  \n"
         "fldl      %[a]       \n"
         "fldl      %[two]     \n"
         "fmulp                \n"
         "fldl      %[result]  \n"
         "fdivp                \n"
         "fstpl     %[result]  \n"
         
         : [result] "=m" (result)
         : [a] "m" (a),
           [b] "m" (b),
           [c] "m" (c),
           [four] "m" (four),
           [two] "m" (two)
         :
     );

  printf("%.2f %.2f %.2f", a, b, c);
  printf(" positive result: %f", result);
  printf("\n\n");
}
