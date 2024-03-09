#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* formatNumber(char* input, char begin, char divider) {
  int length = strlen(input);

  // Determine the length of the formatted string:
  // [length] + [number of dividers] + [1 for begin sign] + [1 for null terminator]
  int formattedLength = length + length / 3 + 2;

  // Allocate memory for the formatted string
  char* formattedNumber = (char*)malloc(formattedLength);

  int j = 0; // index for the formatted string
  int commaCount = length % 3; // determine where the first divider should be placed

  // Add begin sign at the beginning
  formattedNumber[0] = begin;
  j = j + 1;

  // Iterate over the original string from the beginning
  for (int i = 0; i < length; i++) {
      formattedNumber[j] = input[i];
      j = j + 1;


      // Add a divider every three digits, but not after the last digit
      if (commaCount > 0 && i < length - 1 && (i + 1) % 3 == commaCount) {
          formattedNumber[j++] = divider;
      } else if (commaCount == 0 && i < length - 1 && (i + 1) % 3 == 0) {
          formattedNumber[j++] = divider;
      }
  }

  // Null-terminate the formatted string
  formattedNumber[j] = '\0';

  return formattedNumber;
}


// fgetc(readabaleStream) reads each character from stdin
// fprintf(writabaleStream) writes in file
// fflush(writabaleStream) writes imadiatly and does not wait to collect data

int main(int argc, char* argv[]) {

  FILE *outputFile = fopen(argv[1], "w");
  int c = fgetc(stdin);

  // allocate memory to store one complete number into 23 --> [2, 3] [char *number === number stores adress of the numbers characters]
  char *number = (char *)malloc(10 * sizeof(char));
  int index = 0;

  // Keep reading until we got EOF signal. stdin.end() sends this signal from Node.js
  while (c != EOF)
  {

    if (c != ' ') {
      number[index] = c;
      index++;
    }

    if (c == ' ') {

      if (index > 0) {
      // end the string(number) as we completly read it
        number[index] = '\0';

        // format the number we just read
        char* formatedNumber = formatNumber(number, argv[2][0], argv[3][0]);

        // write in destination stream
        fprintf(outputFile, "%s", formatedNumber);
        // fflush(outputFile);

        // reseting... free the memory, free the pointer [ char * ]
        free(number);
        free(formatedNumber);
        number = (char *)malloc(10 * sizeof(char));
        index = 0;
      }

    }

    // read another character from stream
    c = fgetc(stdin);
  }

  // close the file
  fclose(outputFile);

  exit(0);
}