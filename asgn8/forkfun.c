/*
Author: Alex Novitchkov
File: forkfun.c
Assignment for CS201-01

This program forks a given number of children,
inputed from the command line (1 min, 4 max).
If <1, for 1 child and if >4, fork 4 children.
Signals can be sent to the processes when sleeping
and "receiving" messages will get printed out.
At the end, a total amount of signals
while sleeping will be displayed.
Note: All printf statements are broken down for better clarity
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/*
@returns number of forks to execute

Validates fork number from command line
*/
int forkNumValidator();

/*
@param pid - Child's pid

This routine runs through the parent code
*/
void parentRoutine(pid_t pid);

/*
@param pid - Child's pid
@return sigsReceived from child via exit()

This routine runs through the child code
*/
int childRoutine(pid_t pid);

/*
This function is invoked by a SIGUSR1 signal directed to the parent
*/
void sigHandlerUsrParent();

/*
This function is invoked by a SIGUSR1 signal directed to a child
*/
void sigHandlerUsrChild();

/*
This function is invoked by a SIGTERM signal directed to the parent
*/
void sigHandlerTerm();

/* Global variables are necessary because some functions are parameterless */
int* childPids = NULL;
int sigsReceived = 0;
int numForks;
/*-------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  pid_t pid = 1;
  int inputNum;

  inputNum = atoi(argv[1]);

  numForks = forkNumValidator(inputNum);

  childPids = (int*) malloc(numForks + 1);

  if (argc != 2)
  {
    exit(-1);
  }

  printf("\n");
  printf("PARENT: process id is %d", getpid());
  printf("\n\n");
  printf("PARENT: forking %d processes", numForks);
  printf("\n");

  /*
  Forking numForks forks!
  We need to make sure that children do not fork themselves,
  thus create a forkbomb, which is why pid must be > 0!
  */
  for (int i = 0; i < numForks && pid > 0; i++)
  {
    pid = fork();

    childPids[i] = pid;
  }
  /*-----------------------------------------------------*/

  if (pid <= -1)
  {
    printf("fork failed");
    exit(-1);
    printf("\n\n");
  }
  else if (pid == 0)
  {
    childRoutine(pid);
  }
  else
  {
    parentRoutine(pid);
  }
}

/*---------------------------------------*/
int forkNumValidator(int inputNum)
{  
  if (inputNum < 1)
  {
    return 1;
  }
  else if (inputNum > 4)
  {
    return 4;
  }

  return inputNum;
}

/*---------------------------------------*/
void parentRoutine(pid_t pid)
{  
    int childExit;
    int sumOfChildExits;
 
    signal(SIGUSR1, sigHandlerUsrParent);
    signal(SIGTERM, sigHandlerTerm);

    printf("\n");
    printf("PARENT: waiting for child %d to end", pid);
    printf("\n");

    for (int i = 0; i < numForks; i++)
    {
      wait(&childExit); /* Waits for any one of its children to end */
      sumOfChildExits += WEXITSTATUS(childExit);
    }

    printf("\n");
    printf("Sum of child exit values: %d", sumOfChildExits);
    printf("\n");
}

/*---------------------------------------*/
int childRoutine(pid_t pid)
{
  int timeSeconds;
  int sleepRemaining;

  signal(SIGUSR1, sigHandlerUsrChild);

  printf("\n");
  printf("CHILD %d is alive", getpid());
  printf("\n");

  srand(getpid());

  timeSeconds = (rand() % 31) + 30;

  /* The process is going to sleep for some time, timeSeconds */  
  sleepRemaining = sleep(timeSeconds);

  /* If interrupted by a signal, keep sleeping for the remaining time */
  while (sleepRemaining != 0)
  {
    sleepRemaining = sleep(sleepRemaining);
  }
  /*------------------------------------------------------------------*/

  printf("\n");
  printf("Signal(s) %d received while sleeping: %d", getpid(), sigsReceived);
  printf("\n");

  exit(sigsReceived);
}

/*---------------------------*/
void sigHandlerUsrParent()
{
  printf("\n");
  printf("PARENT: SIGUSR1 signal received!");
  printf("\n");

  for (int i = 0; i < numForks; i++)
  {
    kill(childPids[i], SIGUSR1);
  }
}

/*--------------------------*/
void sigHandlerUsrChild()
{
  printf("\n");
  printf("CHILD: SIGUSR1 signal received!");
  printf("\n");

  sigsReceived++;
}

/*-----------------------*/
void sigHandlerTerm()
{
  for (int i = 0; i < numForks; i++)
  {
    kill(childPids[i], SIGKILL);
  }

  raise(SIGKILL);
}
