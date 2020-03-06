/*
Author: Alex Burbank
CS201-01 asgn9
File: stringlist.c
This is the function definitions for the list operations (add, remove, and print) Note: I could not make the list to print out how you wanted it to
*/

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "stringlist.h"

/*-------------------------------------------------------*/
void listAdd(struct node** ptrToHead, char* data)
{
  struct node* newNode = (struct node*) malloc(sizeof(struct node));
  newNode->data = data;
  newNode->next = NULL;

  struct node* current = *ptrToHead;
  struct node* parent = NULL;

  int cStringLength = strlen(data);

  printf("\n");

  printf("Added ");

  for (int i = 0; i < cStringLength; i++)
  {
    printf("%c", data[i]);
  }
  
  if (current == NULL)
  {
    *ptrToHead = newNode;
  }
  else if (current->next == NULL)
  {
    current->next = newNode;
  }
  else
  {
    int found = 0;  /* The following loop needs to break if found otherwise we will loop for potentially a long time */

    while (current != NULL || !found)
    {
      if (strcmp(current->data, newNode->data) >= 0)
      {
        found = 1;
      }
      
      parent = current;
      current = current->next;
    }
    
    if (current == NULL)
    {
      parent->next = newNode;
    }
    else
    {
      newNode->next = current;
      parent->next = newNode;
    }
  }

  newNode = NULL;
  data = NULL;
}

/*-------------------------------------------------------*/
void listRemove(struct node** ptrToHead, char* data)
{
  struct node* removalPtr = *ptrToHead; /* aka current */
  struct node* parent = NULL;
  int cStringLength;
  int found = 0;

  printf("\n");

  while (removalPtr != NULL && !found)
  {
    if (strcmp(removalPtr->data, data) == 0)
    {
      found = 1;
    }

    parent = removalPtr;
    removalPtr = removalPtr->next;
  }

  if (found)
  {
    parent->next = removalPtr->next;
    removalPtr->next == NULL;

    cStringLength = strlen(removalPtr->data);

    free(removalPtr);
  }

  printf("Removed: ");

  for (int i = 0; i < cStringLength; i++)
  {
    printf("%c", data[i]);
  }
}

/*--------------------------------------*/
void listPrint(struct node* ptrToHead)
{
  struct node* current = ptrToHead;
  int cStringLength;

  printf("       List: ");

  while (current != NULL)
  {
    cStringLength = strlen(current->data);

    for (int i = 0; i < cStringLength; i++)
    {
      printf("%c", current->data[i]);
    }
  
    current = current->next;

    printf("  ");
  }
}
