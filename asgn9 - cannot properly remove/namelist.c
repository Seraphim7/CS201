/*
Author: Alex Novitchkov
CS201-01 asgn9
File: namelist.h
Controller of the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlist.h"

/*-----------------------------------*/
int main(int argc, char** argv)
{
  struct node* llhead = NULL;
  char* argStringPtr;
  char action;
  int stringLength;

  printf("Author: Alex Novitchkov");
  printf("\n");
  
  for (int i = 1; i < argc; i++)
  {
    stringLength = strlen(argv[i]);

    argStringPtr = (char*) malloc(stringLength + 1);

    strcpy(argStringPtr, argv[i] + 1);

    action = argv[i][0];

    if (action == '+')
    {
      listAdd(&llhead, argStringPtr);
    }
    else if (action == '-')
    {
      listRemove(&llhead, argStringPtr);
    }

    listPrint(llhead);
  }

  printf("\n");
}
