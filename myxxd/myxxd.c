#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
  int extraSpaces = 16 - size;
  int tmp = extraSpaces / 2;

  //If there are a max 16 chars in this line
  if (extraSpaces == 0) {
    for (size_t i = 0; i < size; i++) {
      if (i % 2) {
        printf("%02x", data[i]);  
      }
      else {
        printf(" %02x", data[i]);  
      }
    }
  }
  //If there are <16 chars and extra spaces need to be printed
  else {
    for (size_t i = 0; i < size; i++) {
      if (i % 2) {
        printf("%02x", data[i]);  
      } 
      else {
        printf(" %02x", data[i]);  
      }  
    }

    //Calculates how many spaces to print
    extraSpaces = extraSpaces * 2;
    extraSpaces = extraSpaces + tmp;
    for (size_t i = 0; i < extraSpaces; i++) {
      printf(" ");
    }
  }
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
  int extraSpaces = 16 - size;

  if (extraSpaces == 0) {
    for (size_t i = 0; i < size; i++) {
      printf("%c", data[i]);
    }
  }
  else
  {
    for (size_t i = 0; i <= size; i++) {
      printf("%c", data[i]);
    }
  }
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  printf("TODO 3: readAndPrintInputAsBits\n");
}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
