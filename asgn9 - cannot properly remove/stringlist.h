/*
Author: Alex Novitchkov
CS201-01 asgn9
File: stringlist.h
This program defines a node for the linked list as well as some function prototypes for various actions
*/

#ifndef LIST
#define LIST

struct node
{
  char* data;
  struct node* next;
};

/*
  @param ptrToHead - a pointer to the head of the linked list
  @param data - data to add to the list

  Adds to the Linked list
*/
void listAdd(struct node** ptrToHead, char* data);

/*
  @param ptrToHead - a pointer to the head of the linked list
  @param data - data to remove from the list

  Removes from the linked list
*/

void listRemove(struct node** ptrToHead, char* data);

/*
  @param ptrToHead - a pointer to the head of the linked list
  
  Print the linked list
*/
void listPrint(struct node* ptrToHead);

#endif
