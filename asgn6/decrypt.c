/*
Author: Alex Novitchkov
CS201-01: Assignment 6
decrypt.c

This proram reads in an encrypted file,
one that has its odd bytes flipped and
the nibbles swapped for the even bytes
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
@param fileName - the name of the file
@param fileData - the imput file's data
@param fileSize - the imput file's size

This function writes the data in fileData to an output file
*/
void WritingFile(char* fileName, char* fileData, int fileSize);

/*
@param fileData - the input file's data
@param fileSize - the input file's size

This function decrypts data
*/
void DecryptingData(char* fileData, int fileSize);

/*---------------------------------*/
int main(int argc, char* argv[])
{
  FILE* rFile;
  char* fileData;
  char* fileName = argv[1];
  unsigned int result;
  unsigned int fileSize;

  printf("\n");

  for (int i = 0; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  
  printf("\n");
  printf("Author:      Alex Novitchkov\n");
  printf("Input file:  %s", argv[1]);
  printf("\n");

  rFile = fopen(fileName, "rb");

  fseek(rFile, 0, SEEK_END);
  fileSize  = ftell(rFile);
  rewind(rFile);

  printf("File size:   %d bytes", fileSize);
  printf("\n");

/* Allocating enough space for the data in the file */
  fileData = (char*) malloc(sizeof(char) * fileSize);

  if (fileData == NULL)
  {
    fputs("Not enough memory error", stderr);
    printf("\n");
    exit(1);
  }

/* Reading data into fileData from rFile */
  result = fread(fileData, 1, fileSize, rFile);

  if (result != fileSize)
  {
    fputs("Reading error", stderr);
    exit(1);
    printf("\n");
  }

  fclose(rFile);
  
  if (rFile == NULL)
  {
    fputs("Error opening file", stderr);
    printf("\n");
    exit(1);
  }

  printf("Output file: %s.d", argv[1]);
  printf("\n");

  DecryptingData(fileData, fileSize);
  WritingFile(argv[1], fileData, fileSize);

  printf("Output file created.");
  printf("\n\n");

  free(fileData);
}

/*------------------------------------------------*/
void DecryptingData(char* fileData, int fileSize)
{
  char lastNibble;  

  for (int i = 0; i < fileSize; i++)
  {
    if (i % 2 == 0) /* if even */
    {
      fileData[i] = fileData[i] ^ 0xFF; /* ex: 10010000 -> 01101111 */
    }
    else
    {
      lastNibble = (fileData[i] >> 4) & 0x0F; /* ex: 10010000 -> 00001001 */
      fileData[i] = (fileData[i] << 4) & 0xF0; /* ex: 10010000 -> 00000000 */
      fileData[i] = fileData[i] | lastNibble; /* ex: 00000000 -> 00001001 */
    }
  }

  printf("Decryption Successful!  ");
}

/*---------------------------------------------------------------*/
void WritingFile(char* fileName, char* fileData, int fileSize)
{
  FILE* wFile;

  fileName = strcat(fileName, ".d");

  wFile = fopen(fileName, "wb");
  fwrite(fileData, sizeof(char), fileSize, wFile);
  fclose(wFile);
}
