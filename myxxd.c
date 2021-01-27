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
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
  int maxSize = 16;
  int extraSpaces = maxSize - size;
  int tmp = extraSpaces / 2;

  //If line has a max size of 16
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
  //If line doesn't have max size and extra spaces need to be printed
  else {
    for (size_t i = 0; i < size; i++) {
      if (i % 2) {
        printf("%02x", data[i]);  
      } 
      else {
        printf(" %02x", data[i]);  
      }  
    }

    //Prints extra spaces
    extraSpaces = extraSpaces * 2;
    extraSpaces = extraSpaces + tmp;
    for (size_t i = 0; i < extraSpaces; i++) {
      printf(" ");
    }
  }
}

void printDataAsBits(unsigned char *data, size_t size) {
  int maxSize = 6;
  int extraSpaces = maxSize - size;
  int tmp = extraSpaces;
  int numBits = 8;

  unsigned char output[numBits];

  //If line has a max size of 6
  if (extraSpaces == 0) {
    for (size_t i = 0; i < size; i++) {
      unsigned char currChar = data[i];
      //Stores bits in reverse order
      for (size_t j = 0; j < numBits; j++) {
        if (currChar % 2) {
          output[j] = 1;
        }
        else
        {
          output[j] = 0;
        }
        currChar = currChar / 2;
      }
      //Prints in correct order
      printf(" ");
      for (size_t j = 1; j <= numBits; j++) {
        printf("%d", output[numBits - j]);
      }
    }

  }
  //If line doesn't have max size and extra spaces need to be printed
  else {
    for (size_t i = 0; i < size; i++) {
      unsigned char currChar = data[i];
      
      //Stores bits in reverse order
      for (size_t j = 0; j < numBits; j++) {
        if (currChar % 2) {
          output[j] = 1;
        }
        else
        {
          output[j] = 0;
        }
        currChar = currChar / 2;
      }
      
      //Prints in correct order
      printf(" ");
      for (size_t j = 1; j <= numBits; j++) {
        printf("%d", output[numBits - j]);
      }
      
      //Prints extra spaces
      extraSpaces = extraSpaces * numBits;
      extraSpaces = extraSpaces + tmp;
      for (size_t i = 0; i < extraSpaces; i++) {
        printf(" ");
      }
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
  for (size_t i = 0; i < size; i++) {
    //Checks if char is out of printable range
    if (data[i] >= 32 && data[i] <= 126) {
      printf("%c", data[i]);
    }
    else {
      printf(".");
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
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[6];
  int numBytesRead = fread(data, 1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsBits(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
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
